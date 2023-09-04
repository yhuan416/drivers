#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/module.h>

#define CHRDEV_MAJOR 0          // 主设备号
#define CHRDEV_NAME "chrdev"    // 设备名

#define CHRDEV_MSG  "hello chrdev"
static char read_buf[100];
static char write_buf[100];

static int major;
static int minor;
static dev_t devid;

static struct cdev chrdev_cdev;

static struct class *class;
static struct device *device;

static int chrdev_open(struct inode *inode, struct file *filp)
{
    printk("chrdev open!\r\n");
    return 0;
}

static ssize_t chrdev_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
    int ret = 0;

    printk("chrdev read!\r\n");

    memcpy(read_buf, CHRDEV_MSG, sizeof(CHRDEV_MSG));
    ret = copy_to_user(buf, read_buf, cnt);
    if (ret < 0)
    {
        printk("chrdev: copy to user failed!\r\n");
        return -EFAULT;
    }

    printk("chrdev: copy to user ok!\r\n");
    return 0;
}

static ssize_t chrdev_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
    int ret = 0;

    printk("chrdev write!\r\n");

    ret = copy_from_user(write_buf, buf, cnt);
    if (ret < 0)
    {
        printk("chrdev: copy from user failed!\r\n");
        return -EFAULT;
    }

    printk("chrdev: copy from user ok!\r\n");
    printk("chrdev: buf = %s\r\n", write_buf);
    return 0;
}

static int chrdev_release(struct inode *inode, struct file *filp)
{
    printk("chrdev release!\r\n");
    return 0;
}

static struct file_operations chrdev_fops =
{
    .owner = THIS_MODULE,
    .open = chrdev_open,
    .read = chrdev_read,
    .write = chrdev_write,
    .release = chrdev_release,
};

static int __init chrdev_init(void)
{
    int ret = 0;

    printk("chrdev_init\r\n");

    // 创建设备号
    if (CHRDEV_MAJOR)
    {
        // 通过主次设备号创建设备号
        devid = MKDEV(CHRDEV_MAJOR, 0);
        major = CHRDEV_MAJOR;
        minor = 0;
    }
    else
    {
        // 申请设备号
        ret = alloc_chrdev_region(&devid, 0, 1, CHRDEV_NAME);
        if (ret < 0)
        {
            printk("chrdev: alloc chrdev region failed!\r\n");
            return -EFAULT;
        }

        major = MAJOR(devid);
        minor = MINOR(devid);
    }

    printk("chrdev: major = %d, minor = %d\r\n", major, minor);

    // 注册字符设备驱动
    chrdev_cdev.owner = THIS_MODULE;
    cdev_init(&chrdev_cdev, &chrdev_fops);

    ret = cdev_add(&chrdev_cdev, devid, 1);
    if (ret < 0)
    {
        printk("chrdev: cdev add failed!\r\n");
        goto del_unregister;
    }

    class = class_create(THIS_MODULE, CHRDEV_NAME);
    if (IS_ERR(class))
    {
        printk("chrdev: class create failed!\r\n");
        goto del_cdev;
    }

    device = device_create(class, NULL, devid, NULL, CHRDEV_NAME);
    if (IS_ERR(device))
    {
        printk("chrdev: device create failed!\r\n");
        goto destroy_class;
    }

    return 0;

destroy_class:
    class_destroy(class);
del_cdev:
    cdev_del(&chrdev_cdev);
del_unregister:
    unregister_chrdev_region(devid, 1);
    return -EFAULT;
}

static void __exit chrdev_exit(void)
{
    device_destroy(class, devid);
    class_destroy(class);

    // 注销字符设备驱动
    cdev_del(&chrdev_cdev);

    // 释放设备号
    unregister_chrdev_region(devid, 1);

    printk("chrdev_exit\r\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yhuan416 <yhuan416@foxmail.com>");
