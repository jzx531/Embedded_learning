// SPDX-License-Identifier: GPL-2.0
/*
 * AT24C02 read/write/llseek 教学示例，按 Linux v5.4 的 I2C API 编写。
 *
 * 节点：/dev/myat24c02
 * 容量：256 字节；文件偏移即 EEPROM 内部地址。
 * read：连续读取；write：逐字节写入，每字节后等待 20 ms。
 *
 * 沿用原代码的单设备全局状态，只允许绑定一个设备。
 * 此示例不处理设备解绑后旧 fd 与重新绑定设备之间的身份隔离；
 * 测试解绑或重新绑定前，应关闭所有打开的 fd。
 * 多设备或支持热插拔的正式驱动应使用每设备状态和引用计数。
 *
 * 新内核的 probe/remove/class_create 接口可能不同，需按目标内核适配。
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>

#define AT24C02_SIZE          256
#define AT24C02_WRITE_WAIT_MS 20
#define AT24C02_CHRDEV_NAME   "at24c02"

static struct i2c_client *at24c02_client;
static int major;
static struct class *at24c02_class;
static DEFINE_MUTEX(at24c02_lock);

static ssize_t at24c02_read(struct file *file, char __user *buf,
                           size_t count, loff_t *ppos)
{
    unsigned char addr;
    unsigned char data[AT24C02_SIZE];
    struct i2c_msg msgs[2];
    int ret;

    if (!count)
        return 0;

    ret = mutex_lock_interruptible(&at24c02_lock);
    if (ret)
        return ret;

    if (!at24c02_client) {
        ret = -ENODEV;
        goto out;
    }

    if (*ppos < 0) {
        ret = -EINVAL;
        goto out;
    }

    /* 到达末尾，返回 EOF。 */
    if (*ppos >= AT24C02_SIZE) {
        ret = 0;
        goto out;
    }

    count = min_t(size_t, count, AT24C02_SIZE - (size_t)*ppos);
    addr = (unsigned char)*ppos;

    /* 同一次传输中先设置内部地址，再以重复 START 发起读取。 */
    msgs[0].addr = at24c02_client->addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = &addr;

    msgs[1].addr = at24c02_client->addr;
    msgs[1].flags = I2C_M_RD;
    msgs[1].len = count;
    msgs[1].buf = data;

    ret = i2c_transfer(at24c02_client->adapter, msgs, 2);
    if (ret != 2) {
        if (ret >= 0)
            ret = -EIO;
        goto out;
    }

    /* 这里持有的是可睡眠的 mutex，不是自旋锁。 */
    if (copy_to_user(buf, data, count)) {
        ret = -EFAULT;
        goto out;
    }

    *ppos += count;
    ret = count;

out:
    mutex_unlock(&at24c02_lock);
    return ret;
}

static ssize_t at24c02_write(struct file *file, const char __user *buf,
                            size_t count, loff_t *ppos)
{
    unsigned char data[AT24C02_SIZE];
    unsigned char byte_buf[2];
    struct i2c_msg msg;
    size_t done = 0;
    int ret;

    if (!count)
        return 0;

    ret = mutex_lock_interruptible(&at24c02_lock);
    if (ret)
        return ret;

    if (!at24c02_client) {
        ret = -ENODEV;
        goto out;
    }

    if (*ppos < 0) {
        ret = -EINVAL;
        goto out;
    }

    if (*ppos >= AT24C02_SIZE) {
        ret = -ENOSPC;
        goto out;
    }

    count = min_t(size_t, count, AT24C02_SIZE - (size_t)*ppos);
    if (copy_from_user(data, buf, count)) {
        ret = -EFAULT;
        goto out;
    }

    msg.addr = at24c02_client->addr;
    msg.flags = 0;
    msg.len = sizeof(byte_buf);
    msg.buf = byte_buf;

    while (done < count) {
        byte_buf[0] = (unsigned char)(*ppos + done);
        byte_buf[1] = data[done];

        ret = i2c_transfer(at24c02_client->adapter, &msg, 1);
        if (ret != 1) {
            if (ret >= 0)
                ret = -EIO;
            break;
        }

        /*
         * 沿用原示例的 20 ms 等待，不在 CPU 上忙等。
         * 实际等待上限应查所用厂商型号的数据手册。
         * 这里只等待，不额外做 ACK 轮询或读回校验。
         */
        msleep(AT24C02_WRITE_WAIT_MS);
        done++;
    }

    /* 部分写入后发生错误时，返回已经完成的字节数。 */
    if (done) {
        *ppos += done;
        ret = done;
    }

out:
    mutex_unlock(&at24c02_lock);
    return ret;
}

static loff_t at24c02_llseek(struct file *file, loff_t offset, int whence)
{
    return fixed_size_llseek(file, offset, whence, AT24C02_SIZE);
}

static const struct file_operations at24c02_fops = {
    .owner = THIS_MODULE,
    .read = at24c02_read,
    .write = at24c02_write,
    .llseek = at24c02_llseek,
};

static int at24c02_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{
    struct device *dev;
    int ret;

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
        return -EOPNOTSUPP;

    /* 此示例只实现普通 7 位从机地址。 */
    if (client->flags & I2C_CLIENT_TEN)
        return -EOPNOTSUPP;

    mutex_lock(&at24c02_lock);
    if (at24c02_client) {
        ret = -EBUSY;
        goto out;
    }

    major = register_chrdev(0, AT24C02_CHRDEV_NAME, &at24c02_fops);
    if (major < 0) {
        ret = major;
        goto out;
    }

    at24c02_class = class_create(THIS_MODULE, "at24c02_class");
    if (IS_ERR(at24c02_class)) {
        ret = PTR_ERR(at24c02_class);
        at24c02_class = NULL;
        goto err_unregister_chrdev;
    }

    dev = device_create(at24c02_class, &client->dev,
                        MKDEV(major, 0), NULL, "myat24c02");
    if (IS_ERR(dev)) {
        ret = PTR_ERR(dev);
        goto err_destroy_class;
    }

    /* 等待锁的 read/write 在这里完成后才能访问 client。 */
    at24c02_client = client;
    dev_info(&client->dev, "created /dev/myat24c02, size=%d bytes\n",
             AT24C02_SIZE);
    ret = 0;
    goto out;

err_destroy_class:
    class_destroy(at24c02_class);
    at24c02_class = NULL;
err_unregister_chrdev:
    unregister_chrdev(major, AT24C02_CHRDEV_NAME);
out:
    mutex_unlock(&at24c02_lock);
    return ret;
}

static int at24c02_remove(struct i2c_client *client)
{
    /* 等待当前读写结束，再阻止后续操作继续使用 client。 */
    mutex_lock(&at24c02_lock);
    at24c02_client = NULL;
    device_destroy(at24c02_class, MKDEV(major, 0));
    class_destroy(at24c02_class);
    at24c02_class = NULL;
    unregister_chrdev(major, AT24C02_CHRDEV_NAME);
    mutex_unlock(&at24c02_lock);
    return 0;
}

static const struct of_device_id at24c02_of_match[] = {
    { .compatible = "100ask,at24c02" },
    { }
};
MODULE_DEVICE_TABLE(of, at24c02_of_match);

static const struct i2c_device_id at24c02_ids[] = {
    { "xxxxyyy", 0 }, /* 保留原示例的非设备树匹配名称。 */
    { "at24c02_rw_demo", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, at24c02_ids);

static struct i2c_driver at24c02_drv = {
    .driver = {
        .name = "my24c02",
        .of_match_table = at24c02_of_match,
    },
    .probe = at24c02_probe,
    .remove = at24c02_remove,
    .id_table = at24c02_ids,
};

static int __init at24c02_init(void)
{
    return i2c_add_driver(&at24c02_drv);
}

static void __exit at24c02_exit(void)
{
    i2c_del_driver(&at24c02_drv);
}

module_init(at24c02_init);
module_exit(at24c02_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("AT24C02 read/write/llseek learning example (Linux v5.4)");
