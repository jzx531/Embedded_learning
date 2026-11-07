#include <linux/module.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#define HELLO_CNT 2   /* 最多支持的设备个数 */

struct hello_dev_data {
    int pin;
    int ker_val;
    struct cdev cdev;
};

static int major = 0;
static struct class *hello_class;

static int hello_open(struct inode *inode, struct file *file)
{
    struct hello_dev_data *data =
        container_of(inode->i_cdev, struct hello_dev_data, cdev);
    file->private_data = data;
    return 0;
}

static ssize_t hello_read(struct file *file, char __user *buf, size_t size, loff_t *offset)
{
    struct hello_dev_data *data = file->private_data;
    printk("%s %s line %d pin=%d\n", __FILE__, __FUNCTION__, __LINE__, data->pin);
    copy_to_user(buf, &data->ker_val, 4);
    return 4;
}

static ssize_t hello_write(struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
    struct hello_dev_data *data = file->private_data;
    printk("%s %s line %d pin=%d\n", __FILE__, __FUNCTION__, __LINE__, data->pin);
    copy_from_user(&data->ker_val, buf, 4);

    if (data->ker_val)
        printk("LED ON (pin %d)\n", data->pin);
    else
        printk("LED OFF (pin %d)\n", data->pin);

    return 4;
}

static struct file_operations hello_fops = {
    .owner      = THIS_MODULE,
    .open       = hello_open,
    .read       = hello_read,
    .write      = hello_write,
};

static int hello_probe(struct platform_device *pdev)
{
    struct hello_dev_data *data;
    int minor;

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    minor = pdev->id;                 /* 每个设备的唯一编号作次设备号 */
    if (minor < 0)
        minor = 0;

    data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

		//通过probe将data绑定到对应cdev
    data->pin = pdev->resource[0].start;
    data->ker_val = 123;

    cdev_init(&data->cdev, &hello_fops);
    data->cdev.owner = THIS_MODULE;
    cdev_add(&data->cdev, MKDEV(major, minor), 1);

    device_create(hello_class, &pdev->dev, MKDEV(major, minor), data, "hello%d", minor);

    platform_set_drvdata(pdev, data);
    return 0;
}

static int hello_remove(struct platform_device *pdev)
{
    struct hello_dev_data *data = platform_get_drvdata(pdev);

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    device_destroy(hello_class, MKDEV(major, pdev->id));
    cdev_del(&data->cdev);
    return 0;
}

static struct platform_driver hello_driver = {
    .probe      = hello_probe,
    .remove     = hello_remove,
    .driver     = {
        .name   = "100ask_hello",
    },
};

static int __init hello_drv_init(void)
{
    dev_t devt;
    int err;

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    err = alloc_chrdev_region(&devt, 0, HELLO_CNT, "hello_drv");
    if (err)
        return err;
    major = MAJOR(devt);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    hello_class = class_create("hello_class");
#else
    hello_class = class_create(THIS_MODULE, "hello_class");
#endif
    if (IS_ERR(hello_class)) {
        unregister_chrdev_region(MKDEV(major, 0), HELLO_CNT);
        return PTR_ERR(hello_class);
    }

    err = platform_driver_register(&hello_driver);
    if (err) {
        class_destroy(hello_class);
        unregister_chrdev_region(MKDEV(major, 0), HELLO_CNT);
    }
    return err;
}

static void __exit hello_drv_exit(void)
{
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    platform_driver_unregister(&hello_driver);
    class_destroy(hello_class);
    unregister_chrdev_region(MKDEV(major, 0), HELLO_CNT);
}

module_init(hello_drv_init);
module_exit(hello_drv_exit);
MODULE_LICENSE("GPL");
