#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <kfifo.h>

/*
struct __kfifo{
	unsigned int in;
	unsigned int out;
	unsigned int nmask;
	unsigned int esize;
	void *data;
};*/



int __init init_module(void)
{
	
	printk("Hello World...welcome\n");
	return 0;
}

void __exit cleanup_module(void)
{
	printk("Bye,..Leaving the world\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmi");
MODULE_DESCRIPTION("A Simple Module");
