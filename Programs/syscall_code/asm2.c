#include<stdio.h>

int main()
{	int ret;
	if(ret==0)
	{
		asm("LDR r7,= #398;"
			"SVC #0;"
			"MOV %[result], r0" : [result] "=r" (ret)
		);
	}
	else if(ret<0)
	{
		perror("test call");
	}
	return 0;
}
