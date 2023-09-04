#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHRDEV_MAJOR 200        // 主设备号
#define CHRDEV_NAME "chrdev"    // 设备名

#define CHRDEV_MSG  "hello chrdev"
static char read_buf[100];
static char write_buf[100];

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

    // 1. 注册字符设备驱动
    ret = register_chrdev(CHRDEV_MAJOR, CHRDEV_NAME, &chrdev_fops);
    if (ret < 0)
    {
        printk("chrdev: register chrdev failed!\r\n");
        return -1;
    }

    return 0;
}

static void __exit chrdev_exit(void)
{
    // 2. 注销字符设备驱动
    unregister_chrdev(CHRDEV_MAJOR, CHRDEV_NAME);

    printk("chrdev_exit\r\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yhuan416 <yhuan416@foxmail.com>");
