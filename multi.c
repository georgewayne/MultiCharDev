#include <linux/slab.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define NUM_DEVS 3

static struct cdev *c_devs; // Global variable for the character device structure array
static struct class *c_cl; // Global variable for the device class
static unsigned int majorNum = 0; //hold dynamically allocated device major number

static int my_open(struct inode *, struct file *);
static int my_close(struct inode *, struct file *);
static ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char __user *buf, size_t, loff_t *);
static struct file_operations mydev_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int mydev_construct(struct cdev *one_dev, int minor, struct class *class)
{
    int ret;
    dev_t devno = MKDEV(majorNum, minor);
    struct device *dev_ret = NULL;

    BUG_ON(class == NULL);

    if (IS_ERR(dev_ret = device_create(class, NULL, devno, NULL, "mydevname%d", minor))) {
        ret = PTR_ERR(dev_ret);
        printk(KERN_INFO "fail device_create while trying to create mydevname%d, \
                code: %d\n", minor, ret);
        return ret;
    }
    cdev_init(one_dev, &mydev_fops);
    if ((ret = cdev_add(one_dev, devno, 1))) {
        printk(KERN_INFO "fail cdev_add wile trying to add mydevname%d, code: %d\n", minor, ret);
        return ret;
    }
    printk(KERN_INFO "mydevname%d sucessfuly created\n", minor);
    return 0;
}

static void dev_cleanup(int num)
{
    int i;
    dev_t devt;
    if (c_devs) {
        for (i = 0; i < num; i++) {
            devt = MKDEV(majorNum, i);
            cdev_del(&c_devs[i]);     
            device_destroy(c_cl, devt);
            unregister_chrdev_region(devt, 1);
            printk(KERN_INFO "mydevname%d unregistered\n", i);
        }
        kfree(c_devs);
    }
    return;
}

static int __init mydev_init(void)
{
    int i;
    int ret;
    int devices_to_destroy = 0;
    dev_t devt = 0; 
    if ((ret = alloc_chrdev_region(&devt, 0, NUM_DEVS, "mydevname")) < 0) {
        printk(KERN_INFO "fail alloc_chrdev_region, code: %d\n", ret);
        return ret;
    }
    majorNum = MAJOR(devt);
    if (IS_ERR(c_cl = class_create(THIS_MODULE, "mycharclass"))) {
        ret = PTR_ERR(c_cl);
        printk(KERN_INFO "fail class_create, code: %d\n", ret);
        goto fail_class_create;
    }
    
    /* Allocate the array of devices */
    if ((c_devs = (struct cdev *)kzalloc(NUM_DEVS * sizeof(struct cdev), GFP_KERNEL)) == NULL) {
        printk(KERN_INFO "fail kzalloc, probably out of memory\n");
        ret = -ENOMEM;
        goto fail_kzalloc;
    }
    /* Construct devices */
    for (i = 0; i < NUM_DEVS; i++) {
        if ((ret = mydev_construct(&c_devs[i], i, c_cl))) {
            devices_to_destroy = i;
            goto fail_mydev_construct;
        }
    }
    printk(KERN_INFO "all %d devices sucessfuly created\n", NUM_DEVS);
    return 0;

fail_mydev_construct:
    dev_cleanup(devices_to_destroy);
fail_kzalloc:
    class_destroy(c_cl);
fail_class_create:
    return ret;
}

static void __exit mydev_exit(void) /* Destructor */
{
    dev_cleanup(NUM_DEVS);
    class_destroy(c_cl);
    printk(KERN_INFO "all %d devices unregistered\n", NUM_DEVS); 
    return;
}

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open() device /dev/mydevname%d\n", MINOR(i->i_cdev->dev));
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close() device /dev/mydevname%d\n", MINOR(i->i_cdev->dev));
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: read() device /dev/mydevname%d\n", MINOR(f->f_inode->i_cdev->dev));
    return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
    loff_t *off)
{
    printk(KERN_INFO "Driver: write() device /dev/mydevname%d\n", MINOR(f->f_inode->i_cdev->dev));
    return len;
}

module_init(mydev_init);
module_exit(mydev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("my name <email@myemail.com>");
MODULE_DESCRIPTION("my First Character Driver");
