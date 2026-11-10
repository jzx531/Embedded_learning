#include <linux/module.h>
#include <linux/poll.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <asm/current.h>

/* 每个按键对应的设备信息结构体 */
struct gpio_key{
	int gpio;                    /* GPIO编号 */
	struct gpio_desc *gpiod;     /* GPIO描述符 */
	int flag;                    /* GPIO标志(如低电平有效) */
	int irq;                     /* 对应的中断号 */
	struct timer_list key_timer; /* 按键去抖定时器 */
	struct tasklet_struct tasklet; /* 中断下半部tasklet */
	struct work_struct work;     /* 中断下半部工作队列 */
} ;

/* 指向所有按键设备的数组 */
static struct gpio_key *gpio_keys_100ask;

/* 主设备号 */
static int major = 0;
/* 设备类 */
static struct class *gpio_key_class;

/* 环形缓冲区：用于保存按键值 */
#define BUF_LEN 128
static int g_keys[BUF_LEN];
static int r, w; /* 读、写指针 */

/* 用于异步通知(fasync)的结构体 */
struct fasync_struct *button_fasync;

/* 计算环形缓冲区下一个位置 */
#define NEXT_POS(x) ((x+1) % BUF_LEN)

/* 判断环形缓冲区是否为空 */
static int is_key_buf_empty(void)
{
	return (r == w);
}

/* 判断环形缓冲区是否已满 */
static int is_key_buf_full(void)
{
	return (r == NEXT_POS(w));
}

/* 向环形缓冲区写入一个按键值 */
static void put_key(int key)
{
	if (!is_key_buf_full())
	{
		g_keys[w] = key;
		w = NEXT_POS(w);
	}
}

/* 从环形缓冲区读出一个按键值 */
static int get_key(void)
{
	int key = 0;
	if (!is_key_buf_empty())
	{
		key = g_keys[r];
		r = NEXT_POS(r);
	}
	return key;
}

/* 声明并初始化等待队列头：用于read时阻塞等待按键 */
static DECLARE_WAIT_QUEUE_HEAD(gpio_key_wait);

/* 定时器超时回调函数：用于按键去抖，超时后再读取按键值 */
static void key_timer_expire(unsigned long data)
{
	/* data ==> gpio_key 结构体指针 */
	struct gpio_key *gpio_key = data;
	int val;
	int key;

	/* 读取GPIO电平值 */
	val = gpiod_get_value(gpio_key->gpiod);


	printk("key_timer_expire key %d %d\n", gpio_key->gpio, val);
	/* 将GPIO编号和电平值打包成一个按键值(高8位为gpio号,低8位为电平值) */
	key = (gpio_key->gpio << 8) | val;
	put_key(key);                                  /* 写入环形缓冲区 */
	wake_up_interruptible(&gpio_key_wait);         /* 唤醒等待队列中阻塞的进程 */
	kill_fasync(&button_fasync, SIGIO, POLL_IN);   /* 向应用层发送异步通知信号 */
}

/* tasklet处理函数：在中断下半部执行 */
static void key_tasklet_func(unsigned long data)
{
	/* data ==> gpio_key 结构体指针 */
	struct gpio_key *gpio_key = data;
	int val;
	int key;

	/* 读取GPIO电平值 */
	val = gpiod_get_value(gpio_key->gpiod);


	printk("key_tasklet_func key %d %d\n", gpio_key->gpio, val);
}

/* 工作队列处理函数：在进程上下文中执行 */
static void key_work_func(struct work_struct *work)
{
	/* 通过work成员反推出所属的gpio_key结构体 */
	struct gpio_key *gpio_key = container_of(work, struct gpio_key, work);
	int val;

	/* 读取GPIO电平值 */
	val = gpiod_get_value(gpio_key->gpiod);

	printk("key_work_func: the process is %s pid %d\n",current->comm, current->pid);	
	printk("key_work_func key %d %d\n", gpio_key->gpio, val);
}

/* 实现对应的open/read/write等函数，填入file_operations结构体 */
/* read函数：读取按键值到用户空间 */
static ssize_t gpio_key_drv_read (struct file *file, char __user *buf, size_t size, loff_t *offset)
{
	//printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	int err;
	int key;

	/* 如果缓冲区为空且以非阻塞方式打开，则直接返回 */
	if (is_key_buf_empty() && (file->f_flags & O_NONBLOCK))
		return -EAGAIN;
	
	/* 缓冲区为空时在此阻塞休眠，直到有按键数据或进程被唤醒 */
	wait_event_interruptible(gpio_key_wait, !is_key_buf_empty());
	key = get_key();                       /* 从缓冲区取按键值 */
	err = copy_to_user(buf, &key, 4);      /* 拷贝到用户空间 */
	
	return 4;
}

/* poll函数：支持应用层select/poll多路复用 */
static unsigned int gpio_key_drv_poll(struct file *fp, poll_table * wait)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	poll_wait(fp, &gpio_key_wait, wait);   /* 把当前进程挂到等待队列 */
	return is_key_buf_empty() ? 0 : POLLIN | POLLRDNORM; /* 有数据则返回可读 */
}

/* fasync函数：支持异步通知 */
static int gpio_key_drv_fasync(int fd, struct file *file, int on)
{
	if (fasync_helper(fd, file, on, &button_fasync) >= 0)
		return 0;
	else
		return -EIO;
}


/* 定义自己的file_operations结构体 */
static struct file_operations gpio_key_drv = {
	.owner	 = THIS_MODULE,
	.read    = gpio_key_drv_read,
	.poll    = gpio_key_drv_poll,
	.fasync  = gpio_key_drv_fasync,
};

/* 中断上半部处理函数：中断发生时被调用 */
static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
	struct gpio_key *gpio_key = dev_id;
	//printk("gpio_key_isr key %d irq happened\n", gpio_key->gpio);
	tasklet_schedule(&gpio_key->tasklet);                  /* 调度tasklet(下半部) */
	mod_timer(&gpio_key->key_timer, jiffies + HZ/50);      /* 重新定时器用于去抖 */
	schedule_work(&gpio_key->work);                        /* 调度工作队列(下半部) */
	return IRQ_WAKE_THREAD;                                /* 唤醒内核线程处理线程化中断 */
}

/* 线程化中断的线程处理函数：在内核线程中执行 */
static irqreturn_t gpio_key_thread_func(int irq, void *data)
{
	struct gpio_key *gpio_key = data;
	int val;

	/* 读取GPIO电平值 */
	val = gpiod_get_value(gpio_key->gpiod);

	printk("gpio_key_thread_func: the process is %s pid %d\n",current->comm, current->pid);	
	printk("gpio_key_thread_func key %d %d\n", gpio_key->gpio, val);
	
	return IRQ_HANDLED;
}


/* probe函数：设备匹配后初始化
 * 1. 从platform_device获得GPIO
 * 2. gpio=>irq
 * 3. request_irq
 */
static int gpio_key_probe(struct platform_device *pdev)
{
	int err;
	struct device_node *node = pdev->dev.of_node;
	int count;
	int i;
	enum of_gpio_flags flag;
		
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	/* 获取设备树中GPIO的数量 */
	count = of_gpio_count(node);
	if (!count)
	{
		printk("%s %s line %d, there isn't any gpio available\n", __FILE__, __FUNCTION__, __LINE__);
		return -1;
	}

	/* 分配count个gpio_key结构体 */
	gpio_keys_100ask = kzalloc(sizeof(struct gpio_key) * count, GFP_KERNEL);
	for (i = 0; i < count; i++)
	{		
		/* 从设备树获取GPIO编号及标志 */
		gpio_keys_100ask[i].gpio = of_get_gpio_flags(node, i, &flag);
		if (gpio_keys_100ask[i].gpio < 0)
		{
			printk("%s %s line %d, of_get_gpio_flags fail\n", __FILE__, __FUNCTION__, __LINE__);
			return -1;
		}
		gpio_keys_100ask[i].gpiod = gpio_to_desc(gpio_keys_100ask[i].gpio); /* 得到GPIO描述符 */
		gpio_keys_100ask[i].flag = flag & OF_GPIO_ACTIVE_LOW;               /* 记录是否低电平有效 */
		gpio_keys_100ask[i].irq  = gpio_to_irq(gpio_keys_100ask[i].gpio);   /* 由GPIO得到中断号 */

		/* 初始化并注册按键去抖定时器 */
		setup_timer(&gpio_keys_100ask[i].key_timer, key_timer_expire, &gpio_keys_100ask[i]);
		gpio_keys_100ask[i].key_timer.expires = ~0;   /* 先设置一个很远的超时时间 */
		add_timer(&gpio_keys_100ask[i].key_timer);

		/* 初始化tasklet */
		tasklet_init(&gpio_keys_100ask[i].tasklet, key_tasklet_func, &gpio_keys_100ask[i]);

		/* 初始化工作队列 */
		INIT_WORK(&gpio_keys_100ask[i].work, key_work_func);
	}

	for (i = 0; i < count; i++)
	{
		/* 注册普通中断(上下半部均在中断上下文) */
		//err = request_irq(gpio_keys_100ask[i].irq, gpio_key_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "100ask_gpio_key", &gpio_keys_100ask[i]);
		/* 注册线程化中断：上升沿和下降沿都触发 */
		err = request_threaded_irq(gpio_keys_100ask[i].irq, gpio_key_isr, gpio_key_thread_func, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "100ask_gpio_key", &gpio_keys_100ask[i]);
	}

	/* 注册file_operations，得到主设备号 */
	major = register_chrdev(0, "100ask_gpio_key", &gpio_key_drv);  /* /dev/gpio_key */

	/* 创建设备类 */
	gpio_key_class = class_create(THIS_MODULE, "100ask_gpio_key_class");
	if (IS_ERR(gpio_key_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "100ask_gpio_key");
		return PTR_ERR(gpio_key_class);
	}

	/* 创建设备节点 /dev/100ask_gpio_key */
	device_create(gpio_key_class, NULL, MKDEV(major, 0), NULL, "100ask_gpio_key"); /* /dev/100ask_gpio_key */
        
    return 0;
    
}

/* remove函数：设备卸载时被调用，释放资源 */
static int gpio_key_remove(struct platform_device *pdev)
{
	//int err;
	struct device_node *node = pdev->dev.of_node;
	int count;
	int i;

	/* 销毁设备节点、设备类和字符设备 */
	device_destroy(gpio_key_class, MKDEV(major, 0));
	class_destroy(gpio_key_class);
	unregister_chrdev(major, "100ask_gpio_key");

	/* 释放中断、定时器、tasklet等资源 */
	count = of_gpio_count(node);
	for (i = 0; i < count; i++)
	{
		free_irq(gpio_keys_100ask[i].irq, &gpio_keys_100ask[i]);
		del_timer(&gpio_keys_100ask[i].key_timer);
		tasklet_kill(&gpio_keys_100ask[i].tasklet);
	}
	kfree(gpio_keys_100ask); /* 释放设备数组 */
    return 0;
}

/* 设备树匹配表：与设备树中的compatible属性匹配 */
static const struct of_device_id ask100_keys[] = {
    { .compatible = "100ask,gpio_key" },
    { },
};

/* 1. 定义platform_driver */
static struct platform_driver gpio_keys_driver = {
    .probe      = gpio_key_probe,
    .remove     = gpio_key_remove,
    .driver     = {
        .name   = "100ask_gpio_key",
        .of_match_table = ask100_keys,
    },
};

/* 2. 在入口函数注册platform_driver */
static int __init gpio_key_init(void)
{
    int err;
    
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	
    err = platform_driver_register(&gpio_keys_driver); 
	
	return err;
}

/* 3. 有入口函数就应该有出口函数：卸载驱动程序时，就会去调用这个出口函数
 *     卸载platform_driver
 */
static void __exit gpio_key_exit(void)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

    platform_driver_unregister(&gpio_keys_driver);
}


/* 7. 其他完善：提供设备信息，自动创建设备节点 */

module_init(gpio_key_init);
module_exit(gpio_key_exit);

MODULE_LICENSE("GPL");
