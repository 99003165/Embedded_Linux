#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include<linux/kfifo.h>

#define	MAX_SIZE 	1024
#define	IOC_MAGIC 	'p'
#define	MY_IOCTL_LEN	_IO(IOC_MAGIC, 1)
#define	MY_IOCTL_AVAIL	_IO(IOC_MAGIC, 2)
#define	MY_IOCTL_RESET	_IO(IOC_MAGIC, 3)

struct pseudo_stat {
	int len;
	int avail;
}stat;

#define	MY_IOCTL_PSTAT	_IOR(IOC_MAGIC, 4, struct pseudo_stat)

typedef struct priv_obj 
{
	struct cdev cdev;
	struct kfifo myfifo;
	struct device* pdev;
	struct list_head lentry;
}PRIV_OBJ;

LIST_HEAD(mydevlist);

struct class *pclass;

int buflen=0;
int ret, i=0;
size_t rcount, wcount;

int pseudo_open(struct inode* inode , struct file* file)
{
	PRIV_OBJ *pobj = container_of(inode->i_cdev, PRIV_OBJ, cdev);
	file->private_data=pobj;
	printk("Pseudo--open method\n");
	return 0;
}

int pseudo_close(struct inode* inode , struct file* file)
{
	printk("Pseudo--release method\n");
	return 0;
}

ssize_t pseudo_read(struct file * file, char __user * ubuf , size_t size, loff_t * off)
{
	PRIV_OBJ *pobj = file->private_data;
	if(kfifo_is_empty(&pobj->myfifo)) 
	{
		printk("buffer is empty\n");
		return 0;
	}

	rcount = size;
	if(rcount > kfifo_len(&pobj->myfifo))
		rcount = kfifo_len(&pobj->myfifo);
	char *tbuf = kmalloc(rcount, GFP_KERNEL);
	
	ret=kfifo_out(&pobj->myfifo, tbuf, rcount);
	ret = copy_to_user(ubuf, tbuf, rcount);
	kfree(tbuf);
	
	printk("Pseudo--read method\n");
	return rcount;
	
}

ssize_t pseudo_write(struct file * file, const char __user * ubuf , size_t size, loff_t * off)
{
	PRIV_OBJ *pobj = file->private_data;
	if(kfifo_is_full(&pobj->myfifo))
	{
		printk("buffer is full\n");
		return -ENOSPC;
	}
	wcount = size;
	if(wcount > kfifo_avail(&pobj->myfifo))
		wcount = kfifo_avail(&pobj->myfifo);
	
	char *tbuf=kmalloc(wcount, GFP_KERNEL);
	ret = copy_from_user(tbuf, ubuf, wcount);

	kfifo_in(&pobj->myfifo, tbuf, wcount);
	kfree(tbuf);

	printk("Pseudo--write method\n");
	return wcount;
	
}

static long pseudo_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	PRIV_OBJ *pobj = file->private_data;
	printk("Pseudo--ioctl method\n");
	switch (cmd) 
	{
		/*case MY_IOCTL_LEN :
			printk("ioctl--kfifo length is %d\n", kfifo_len(&pobj->myfifo));
			break;
		case MY_IOCTL_AVAIL:
			printk("ioctl--kfifo avail is %d\n", kfifo_avail(&pobj->myfifo));
			break;
		case MY_IOCTL_RESET:
			printk("ioctl--kfifo got reset\n");
			kfifo_reset(&pobj->myfifo);
			break;*/
		case MY_IOCTL_PSTAT:
			printk("ioctl--kfifo statistics\n");
			stat.len=kfifo_len(&pobj->myfifo);
			stat.avail=kfifo_avail(&pobj->myfifo);
			ret=copy_to_user( (char __user*)arg, &stat, sizeof(struct pseudo_stat));
			if(ret) 
			{
				printk("error in copy_to_user\n");
				return -EFAULT;
			}
			break;	
	}
	return 0;
}	

struct file_operations fops = 
{
	.open = pseudo_open,
	.release = pseudo_close,
	.write = pseudo_write,
	.read = pseudo_read,
	.unlocked_ioctl = pseudo_ioctl
};

dev_t pdevid;
int ndevices;
module_param(ndevices, int, S_IRUGO);

static int __init pseudo_init(void)
{	
	PRIV_OBJ *pobj;
	pclass = class_create(THIS_MODULE, "pseudo_class");
        ret = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
        if(ret)
        {
                printk("Pseudo: Failed to register Driver\n");
                return -EINVAL;
        }
        printk("Successfully registered, major = %d, minor = %d\n", MAJOR(pdevid), MINOR(pdevid));
        printk("Pseudo Driver Sample.. Welcome\n");
        
        for( i=0; i < ndevices; i++)
        {
        	pobj = kmalloc(sizeof(PRIV_OBJ), GFP_KERNEL);
        	if(pobj == NULL)
        		printk("NULL pointer");
        
        	ret=kfifo_alloc(&pobj->myfifo, MAX_SIZE, GFP_KERNEL);
        	cdev_init(&pobj->cdev, &fops);
		kobject_set_name(&pobj->cdev.kobj,"pdevice%d",i);
		ret = cdev_add(&pobj->cdev, pdevid+i, 1);
		pobj->pdev = device_create(pclass, NULL, pdevid+i, NULL, "psample%d",i);
		
		list_add_tail(&pobj->lentry, &mydevlist);
	}
	return 0;
}

static void __exit pseudo_exit(void)
{
        
        struct list_head *pcur, *prev;
        list_for_each_safe(pcur, prev, &mydevlist)
        {
        	PRIV_OBJ *pobj = list_entry(pcur, PRIV_OBJ, lentry);
        	kfifo_free(&pobj->myfifo);
        	cdev_del(&pobj->cdev);
        	device_destroy(pclass, pdevid+i);
        	kfree(pobj);
        	i++;
        }
        unregister_chrdev_region(pdevid, ndevices);
        class_destroy(pclass);
        printk("Pseudo Driver Sample.. Bye\n");
}


module_init(pseudo_init);
module_exit(pseudo_exit);
MODULE_LICENSE("GPL");
