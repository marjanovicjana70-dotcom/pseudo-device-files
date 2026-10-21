#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/cdev.h>

ssize_t dumpOutput(struct file *filp,const char __user *userBuffer, size_t byteCount, loff_t *offset);
ssize_t dumpInput(struct file *filp, char __user *userBuffer, size_t byteCount, loff_t *offset);
int dumpOpen(struct inode *inode, struct file *filp);
int dumpRelease(struct inode *inode, struct file *filp);


int major_num = 0;
int minor_num = 0;
dev_t device_num = 0;

static struct cdev *byteDumpDevice; //treba nam cdev_alloc jer je ovo pokazivac

static const struct file_operations byteDump_fop = {
    .owner = THIS_MODULE,
    .write = dumpOutput,
    .read = dumpInput,
    .open = dumpOpen,
    .release = dumpRelease

};

static int byteDumpInit(void){

int success = 0; 


if(major_num){

    device_num = MKDEV(major_num, minor_num);
    success = register_chrdev_region(device_num, 1, "byteDump");

}

else {

success = alloc_chrdev_region(&device_num, 0, 1, "byteDump");
major_num = MAJOR(device_num);

}

if(success < 0){
    printk(KERN_ERR "Couldn't allocate a device number\n");
    return success;
}

byteDumpDevice = cdev_alloc();
byteDumpDevice->ops = &byteDump_fop;
byteDumpDevice->owner = THIS_MODULE;

success = cdev_add(byteDumpDevice, device_num, 1);

if(success < 0){

printk(KERN_ERR "Couldn't add the char device to kernel's list of devices.\n");
unregister_chrdev_region(device_num, 1);
return success;

}

return success;



}

 
static int __init enter_byteDump(void){

int result = byteDumpInit();

if(!result){
    printk(KERN_INFO "Successfully initialized a char device.\n");
}
else {

    printk(KERN_INFO "Unsuccessfully initialized made a char device.\n");

}

return result;

}

static void __exit exit_byteDump(void){

cdev_del(byteDumpDevice);
unregister_chrdev_region(device_num, 1);

printk(KERN_INFO "Unloaded the module.\n");

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jana");

module_init(enter_byteDump);
module_exit(exit_byteDump);


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

