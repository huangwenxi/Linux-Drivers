#include <linux/module.h>   
#include <linux/types.h>   
#include <linux/fs.h>   
#include <linux/errno.h>   
#include <linux/mm.h>   
#include <linux/sched.h>   
#include <linux/init.h>   
#include <linux/cdev.h>   
#include <asm/io.h>   
#include <asm/system.h>   
#include <asm/uaccess.h>   
#include <linux/device.h>  

static struct class *firstdrv_class;
static struct class_device *first_class_dev;
static int major;
int u;

static int first_drv_open(struct inode*inode, struct file *file)
{
	printk("first_drv open!!!\n");
	return 0;
}
static int first_drv_release(struct inode*inode, struct file *file)
{
	printk("first_drv release!!!\n");
	return 0;
}

static int first_drv_read(struct file *file, char __user *user, size_t size, loff_t *loff)
{
	copy_to_user(user,&u,size);
	printk("first_drv read %d!!!\n",u);
	return 1;
}
static int first_drv_write(struct file *file, char __user *user, size_t size, loff_t *loff)
{
	
	copy_from_user(&u,user,size);
	printk("first_frv write %d!!!\n",u);
	return 1;
}
static struct  file_operations first_drv_ops={
	.owner = THIS_MODULE,
	.open = first_drv_open,
	.release = first_drv_release,
	.write = first_drv_write,
	.read = first_drv_read
};

static int  first_drv_init(void)
{
	printk("%d\n",__LINE__);
	//cat /proc/devices
	major = register_chrdev(0, "first_drv_proc", &first_drv_ops);
	printk("%d\n",__LINE__);
	//ls /sys/class/first_drv
	firstdrv_class = class_create(THIS_MODULE, "first_drv_sys");
	printk("%d\n",__LINE__);
	if(unlikely(IS_ERR(firstdrv_class)))
	{
		printk("%d\n",__LINE__);
		return PTR_ERR(firstdrv_class);
	}
			
	printk("%d\n",__LINE__);
	//ls /dev/first_drv
	first_class_dev = class_device_create(firstdrv_class,NULL,MKDEV(major,0),NULL,"first_drv_dev");

	printk("%d\n",__LINE__);
	return 0;
}

static void  first_drv_exit(void)
{
	unregister_chrdev(major, "first_drv_proc");
	class_device_unregister(first_class_dev);
	class_destroy(firstdrv_class);
}
module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_AUTHOR("wenxiHuang");  
MODULE_DESCRIPTION("JZ2440 Test Driver");  
MODULE_VERSION("1.0");  
MODULE_LICENSE("GPL");  


