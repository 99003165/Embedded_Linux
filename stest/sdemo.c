#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int svar=100;
void sayHello(void){}

static int __init sdemo_init(void) 
{
	int i;
	for(i=1;i<=4;i++)
		printk("sdemo, i=%d\n",svar);
	return 0;
}

static void __exit sdemo_exit(void) 
{
	printk("Bye,Leaving the world\n");
}

module_init(sdemo_init);
module_exit(sdemo_exit);
EXPORT_SYMBOL_GPL(svar);
EXPORT_SYMBOL_GPL(sayHello);
