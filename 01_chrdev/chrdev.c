#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init chrdev_init(void)
{
    printk("chrdev_init\n");
    return 0;
}

static void __exit chrdev_exit(void)
{
    printk("chrdev_exit\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yhuan416<yhuan416@foxmail.com>");
MODULE_DESCRIPTION("A simple example Linux module.");
