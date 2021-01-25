#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(mytestcall)
{
	printk("This is my test call\n");
	return 0;
}

SYSCALL_DEFINE2(testcall, int, x, int, y)
{
	printk("The sum is obtained %d\n", x+y);
	return x+y;
}

SYSCALL_DEFINE2(mytestcall2, const char*, buf, size_t, nbytes)
{
        char tbuf[64];
	int ret;
	ret=copy_from_user(tbuf, buf, nbytes);
	printk("%s",tbuf);
	//printk("The string obtained is %s\n",tbuf );
        return 0;
}

SYSCALL_DEFINE3(testecho,const char*, src, char*, dest, size_t, nbytes)
{
	char tbuf[64];
	int ret; 
	ret=copy_from_user(tbuf, src, nbytes);
	printk("%s", tbuf);
	ret=copy_to_user(dest,tbuf, nbytes);

	return nbytes ;
}


SYSCALL_DEFINE1(structcall, const struct sample *, ptr)
{
	struct sample temp;
	int ret;
	ret=copy_from_user(&temp, ptr, sizeof(struct sample));
	if(ret==0)
	{
		printk("%d\n",temp.x);
		printk("%d\n", temp.y);
		printk("%d\n",temp.z);
	}
	return 0;
}

SYSCALL_DEFINE1(structcall2, struct sample *, ptr)
{
        struct sample temp;
        int ret;
        ret=copy_from_user(&temp, ptr, sizeof(struct sample));
	temp.x=10;
	temp.y=20;
	temp.z=30;
	ret=copy_to_user(ptr, &temp, sizeof(struct sample));
        return 0;
}

