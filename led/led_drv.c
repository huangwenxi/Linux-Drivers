#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>


static struct class *ledclass;
static struct class_device *ledclass_dev[4];
static int major;
char *devname[4]={"leds","led1","led2","led3"};

int to;
static int led_open (struct inode *inode, struct file *file)
{
	if(MINOR(inode->i_rdev)==0)
	{
		s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPIO_OUTPUT);
		s3c2410_gpio_cfgpin(S3C2410_GPF5, S3C2410_GPIO_OUTPUT);
		s3c2410_gpio_cfgpin(S3C2410_GPF6, S3C2410_GPIO_OUTPUT);
		printk("leds open\n");
	}
	if(MINOR(inode->i_rdev)==1)
	{
		s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPIO_OUTPUT);
		printk("led1 open\n");
		
	}
	if(MINOR(inode->i_rdev)==2)
	{
		s3c2410_gpio_cfgpin(S3C2410_GPF5, S3C2410_GPIO_OUTPUT);
		printk("led2 open\n");
	}
	if(MINOR(inode->i_rdev)==3)
	{
		s3c2410_gpio_cfgpin(S3C2410_GPF6, S3C2410_GPIO_OUTPUT);
		printk("led3 open\n");
	}
	return 0;
}
static int led_close (struct inode *inode, struct file *file)
{
	
}

ssize_t led_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
	
}
ssize_t led_write (struct file *file, const char __user *user, size_t size, loff_t *loff)
{
	copy_from_user(&to,user,1);
	
	
	if(to == 0)
	{	
		if(MINOR(file->f_mapping->host->i_rdev)==0)
		{
			s3c2410_gpio_setpin(S3C2410_GPF4, 0);
			s3c2410_gpio_setpin(S3C2410_GPF5, 0);
			s3c2410_gpio_setpin(S3C2410_GPF6, 0);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==1)
		{
			s3c2410_gpio_setpin(S3C2410_GPF4, 0);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==2)
		{
			s3c2410_gpio_setpin(S3C2410_GPF5, 0);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==3)
		{
			s3c2410_gpio_setpin(S3C2410_GPF6, 0);
		}
	}
	else
	{	if(MINOR(file->f_mapping->host->i_rdev)==0)
		{
			s3c2410_gpio_setpin(S3C2410_GPF4, 1);
			s3c2410_gpio_setpin(S3C2410_GPF5, 1);
			s3c2410_gpio_setpin(S3C2410_GPF6, 1);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==1)
		{
			s3c2410_gpio_setpin(S3C2410_GPF4, 1);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==2)
		{
			s3c2410_gpio_setpin(S3C2410_GPF5, 1);
		}
		if(MINOR(file->f_mapping->host->i_rdev)==3)
		{
			s3c2410_gpio_setpin(S3C2410_GPF6, 1);
		}
	}
}

static struct file_operations led_ops = {
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_close,
	.read = led_read,
	.write = led_write,
};

static void led_init()
{
	 int devnum = 0;
	 printk("%d\n",__LINE__);
	 major = register_chrdev(0,"led_proc",&led_ops);
	 printk("%d\n",__LINE__);
	 ledclass = class_create(THIS_MODULE,"led_class");
	 printk("%d\n",__LINE__);
	 for(devnum=0;devnum<4;devnum++)
	 {
		ledclass_dev[devnum] = class_device_create(ledclass,NULL,MKDEV(major,devnum),NULL,devname[devnum]);
	 }
	 printk("%d\n",__LINE__);
}

static void led_exit()
{
	int devnum = 0; 
	unregister_chrdev(major,"led_proc");
	for(devnum=0;devnum<4;devnum++)
	{
		class_device_unregister(ledclass_dev[devnum]);
	}
	class_destroy(ledclass);
}

module_init(led_init);
module_exit(led_exit);

MODULE_AUTHOR("wenxiHuang");  
MODULE_DESCRIPTION("JZ2440 Test Driver");  
MODULE_VERSION("1.0");  
MODULE_LICENSE("GPL");  

