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

int32_t value = 0;
char buf[20] = "test procfs\n";
static int len = 1;

dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
static struct proc_dir_entry *parent;

static ssize_t read_proc(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
    if (len)
        len = 0;
    else
    {
        len = 1;
        return 0;
    }

    if (copy_to_user(buffer, buf, 20))
        pr_err("Data Send Error!\n");

    return length;
}

static ssize_t write_proc(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    if (copy_from_user(buf, buff, len))
        pr_err("Data Write Error\n");
    return len;
}

#if (LINUX_KERNEL_VERSION > 505)
static struct proc_ops proc_fops = {
    .proc_read = read_proc,
    .proc_write = write_proc,
};
#else  // LINUX_KERNEL_VERSION > 505
static struct file_operations proc_fops = {
    .read = read_proc,
    .write = write_proc,
};
#endif // LINUX_KERNEL_VERSION > 505

static struct file_operations fops = {
    .owner = THIS_MODULE,
};

static int __init _driver_init(void)
{
    if ((alloc_chrdev_region(&dev, 0, 1, "my_dev")) < 0)
        return -1;

    cdev_init(&my_cdev, &fops);

    if ((cdev_add(&my_cdev, dev, 1)) < 0)
        goto r_class;

    if (IS_ERR(dev_class = class_create(THIS_MODULE, "my_class")))
        goto r_class;

    if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "my_device")))
        goto r_device;

    if (IS_ERR(parent = proc_mkdir("my_proc", NULL)))
        goto r_device;
    proc_create("my_entry", 0666, parent, &proc_fops);

    return 0;

r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

static void __exit _driver_exit(void)
{
    proc_remove(parent);
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev, 1);
}

module_init(_driver_init);
module_exit(_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yhuan416 <yhuan416@foxmail.com>");
MODULE_DESCRIPTION("Simple Linux device driver");
