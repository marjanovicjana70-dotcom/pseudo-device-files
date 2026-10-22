#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/cdev.h>

#define DEVICE_MINOR 1


ssize_t dumpOutput(struct file *filp,const char __user *userBuffer, size_t byteCount, loff_t *offset);
ssize_t dumpInput(struct file *filp, char __user *userBuffer, size_t byteCount, loff_t *offset);
int dumpOpen(struct inode *inode, struct file *filp);
int dumpRelease(struct inode *inode, struct file *filp);


ssize_t spamOutput(struct file *filp,const char __user *userBuffer, size_t byteCount, loff_t *offset);
ssize_t spamInput(struct file *filp, char __user *userBuffer, size_t byteCount, loff_t *offset);
int spamOpen(struct inode *inode, struct file *filp);
int spamRelease(struct inode *inode, struct file *filp);

int major_num = 0;
dev_t device_num = 0;

static struct cdev *PseudoDevice; //treba nam cdev_alloc jer je ovo pokazivac

static const struct file_operations byteDump_fop = {
    .owner = THIS_MODULE,
    .write = dumpOutput,
    .read = dumpInput,
    .open = dumpOpen,
    .release = dumpRelease

};

static const struct file_operations spamZero_fop = {

    .open = spamOpen,
    .release = spamRelease,
    .read = spamInput,
    .write = spamOutput

};

static void successInit(const char *s, int success, int *returnStatus){

if(!success){

printk(KERN_INFO "Successfully initialized a char device - %s\n", s);

}

else {
    *returnStatus = -1;
    printk(KERN_ERR "Unsuccessfully initialized a char device - %s\n", s);
    
}

}

 
static int __init enter_PseudoDrivers(void){

int returnStatus = 0;

if(major_num){

    device_num = MKDEV(major_num, 0);
    success = register_chrdev_region(device_num, 4, "PseudoDevice");
}

else {

success = alloc_chrdev_region(&device_num, 0, 4, "PseudoDevice");
major_num = MAJOR(device_num);

}

if(success < 0){
    printk(KERN_ERR "Couldn't allocate a device number\n");
    return success;
}


successInit("byteDump",byteDumpInit(), &returnStatus);
successInit("spamZero",spamZeroInit(), &returnStatus);

return returnStatus;

}

static void __exit exit_PseudoDrivers(void){

cdev_del(PseudoDevice);
unregister_chrdev_region(device_num, 4);

printk(KERN_INFO "Unloaded modules.\n");

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jana");

module_init(enter_PseudoDrivers);
module_exit(exit_PseudoDrivers);

ssize_t dumpOutput(struct file *filp, const char __user *userBuffer, size_t byteCount, loff_t *offset) {

  offset += byteCount;
    return byteCount;
}

ssize_t dumpInput(struct file *filp, char __user *userBuffer, size_t byteCount, loff_t *offset){

  
    return 0;
}

int dumpOpen(struct inode *inode, struct file *filp){

return 0;

}

int dumpRelease(struct inode *inode, struct file *filp){

return 0;


}

