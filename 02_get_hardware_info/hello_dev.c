#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>

static void hello_dev_release(struct device *dev)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
}

static struct resource hello_res[2] = {
	{
		.start = 2, /* pin2 */
		.end   = 2, /* pin2 */
		.flags = IORESOURCE_TYPE_BITS,
	},
	{
		.start = 3, /* pin3 */
		.end   = 3, /* pin3 */
		.flags = IORESOURCE_TYPE_BITS,
	},
};

static struct platform_device dev0 = {
        .name = "100ask_hello",
        .id   = 0,
        .dev = {
                .release = hello_dev_release,
         },
        .num_resources = 1,
        .resource      = &hello_res[0],
};

static struct platform_device dev1 = {
        .name = "100ask_hello",
        .id   = 1,
        .dev = {
                .release = hello_dev_release,
         },
        .num_resources = 1,
        .resource      = &hello_res[1],
};

static int __init hello_dev_init(void)
{
    int err;
    
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    err = platform_device_register(&dev0);
    if (err)
        return err;

    err = platform_device_register(&dev1);
    
    return err;
}

static void __exit hello_dev_exit(void)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    platform_device_unregister(&dev1);
    platform_device_unregister(&dev0);
}

module_init(hello_dev_init);
module_exit(hello_dev_exit);

MODULE_LICENSE("GPL");
