#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/err.h>

#ifndef LINUX_KERNEL_VERSION
#define LINUX_KERNEL_VERSION 510
#endif

static int __init _driver_init(void)
{
    printk(KERN_INFO "Hello, world\n");
    return 0;
}

static void __exit _driver_exit(void)
{
    printk(KERN_INFO "Goodbye, world\n");
}

module_init(_driver_init);
module_exit(_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yhuan416 <yhuan416@foxmail.com>");
MODULE_DESCRIPTION("Simple Linux device driver");
