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

dev_t pdevid;
int ndevices=1;

struct kfifo myfifo;

int ret, i=0;
struct cdev cdev;
struct device *pdev;
struct class *pclass;

unsigned char *pbuffer;
int rd_offset=0;
int wr_offset=0;
int buflen=0;
size_t rcount, wcount;

int pseudo_open(struct inode* inode , struct file* file)
{
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
	if(kfifo_is_empty(&myfifo)) 
	{
		printk("buffer is empty\n");
		return 0;
	}

	rcount = size;
	if(rcount > kfifo_len(&myfifo))
		rcount = kfifo_len(&myfifo);
	char *tbuf = kmalloc(rcount, GFP_KERNEL);
	
	kfifo_out(&myfifo, tbuf, rcount);
	ret = copy_to_user(ubuf, tbuf, rcount);
	kfree(tbuf);
	
	printk("Pseudo--read method\n");
	return rcount;
}

ssize_t pseudo_write(struct file * file, const char __user * ubuf , size_t size, loff_t * off)
{
	if(kfifo_is_full(&myfifo))
	{
		printk("buffer is full\n");
		return -ENOSPC;
	}
	wcount = size;
	if(wcount > kfifo_avail(&myfifo))
		wcount = kfifo_avail(&myfifo);
	
	char *tbuf=kmalloc(wcount, GFP_KERNEL);
	ret = copy_from_user(tbuf, ubuf, wcount);

	kfifo_in(&myfifo, tbuf, wcount);
	kfree(tbuf);

	printk("Pseudo--write method\n");
	return wcount;
}



struct file_operations fops = {
.open = pseudo_open,
.release = pseudo_close,
.write = pseudo_write,
.read = pseudo_read
};


static int __init pseudo_init(void)
{
	pclass = class_create(THIS_MODULE, "pseudo_class");
        ret = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
        if(ret)
        {
                printk("Pseudo: Failed to register Driver\n");
                return -EINVAL;
        }
        printk("Successfully registered, major = %d, minor = %d\n", MAJOR(pdevid), MINOR(pdevid));
        printk("Pseudo Driver Sample.. Welcome\n");
        cdev_init(&cdev, &fops);
	kobject_set_name(&cdev.kobj,"pdevice%d",i);
	ret = cdev_add(&cdev, pdevid, 1);
	pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d",i);
	pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
	kfifo_init(&myfifo, pbuffer, MAX_SIZE);
	return 0;
}

static void __exit pseudo_exit(void)
{
        unregister_chrdev_region(pdevid, ndevices);
        printk("Pseudo Driver Sample.. Bye\n");
        cdev_del(&cdev);
	//kfree(pbuffer);
	kfifo_free(&myfifo);
	device_destroy(pclass, pdevid);
	class_destroy(pclass);
}


module_init(pseudo_init);
module_exit(pseudo_exit);
MODULE_LICENSE("GPL");
