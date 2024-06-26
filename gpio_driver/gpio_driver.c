#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#define DEVICE_NAME "gpio_driver"

static int major_number;
static struct gpio_desc *gpio_desc;
static int gpio_state = 0;
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .write = device_write,
};
static int gpio_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    int ret;

    printk(KERN_INFO "GPIO_DRIVER: Probe function called for device: %s\n", dev_name(dev));

    gpio_desc = devm_gpiod_get(dev, NULL, GPIOD_OUT_LOW);
    if (IS_ERR(gpio_desc)) {
        ret = PTR_ERR(gpio_desc);
        printk(KERN_ERR "GPIO_DRIVER: Failed to get GPIO descriptor, error: %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "GPIO_DRIVER: GPIO descriptor obtained successfully\n");

    ret = gpiod_direction_output(gpio_desc, 0);
    if (ret) {
        printk(KERN_ERR "GPIO_DRIVER: Failed to set GPIO direction, error: %d\n", ret);
        return ret;
    }

    printk(KERN_INFO "GPIO_DRIVER: GPIO direction set to output\n");

    return 0;
}

static int gpio_remove(struct platform_device *pdev) {
    gpiod_put(gpio_desc);
    return 0;
}

static const struct of_device_id gpio_of_match[] = {
    { .compatible = "my,gpio-device" },
    {},
};
MODULE_DEVICE_TABLE(of, gpio_of_match);

static struct platform_driver gpio_driver = {
    .driver = {
        .name = DEVICE_NAME,
        .of_match_table = gpio_of_match,
    },
    .probe = gpio_probe,
    .remove = gpio_remove,
};

static int __init gpio_driver_init(void) {
    int result;

    printk(KERN_INFO "GPIO_DRIVER: Initializing the GPIO driver\n");

    result = platform_driver_register(&gpio_driver);
    if (result) {
        printk(KERN_ERR "GPIO_DRIVER: Failed to register platform driver\n");
        return result;
    }

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "GPIO_DRIVER: Failed to register a major number\n");
        platform_driver_unregister(&gpio_driver);
        return major_number;
    }
    printk(KERN_INFO "GPIO_DRIVER: Registered correctly with major number %d\n", major_number);

    return 0;
}

static void __exit gpio_driver_exit(void) {
    printk(KERN_INFO "GPIO_DRIVER: Exiting the GPIO driver\n");
    unregister_chrdev(major_number, DEVICE_NAME);
    platform_driver_unregister(&gpio_driver);
    printk(KERN_INFO "GPIO_DRIVER: Goodbye from the LKM!\n");
}

static int device_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "GPIO_DRIVER: Device has been opened\n");
    return 0;
}

static int device_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "GPIO_DRIVER: Device successfully closed\n");
    return 0;
}

static ssize_t device_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset) {
    char buf;
    if (copy_from_user(&buf, buffer, 1)) {
        return -EFAULT;
    }
    printk(KERN_INFO "GPIO_DRIVER: Received write: %c\n", buf);

    if (buf == '1') {
        gpiod_set_value(gpio_desc, 1);
        gpio_state = 1;
        printk(KERN_INFO "GPIO_DRIVER: GPIO set to high\n");
    } else if (buf == '0') {
        gpiod_set_value(gpio_desc, 0);
        gpio_state = 0;
        printk(KERN_INFO "GPIO_DRIVER: GPIO set to low\n");
    } else {
        printk(KERN_INFO "GPIO_DRIVER: Invalid value\n");
        return -EINVAL;
    }
    return len;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux char driver for GPIO control");
MODULE_VERSION("0.1");

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);
