#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define __NR_structcall2 403

struct sample {
int x;
int y;
int z;
};

int main() 
{
	int ret;
	struct sample s1;
	ret = syscall(__NR_structcall2, &s1);
	if(ret<0)
		perror("String Call");
	else
		printf("x= %d, y= %d, z=%d", s1.x, s1.y, s1.z);
	return 0;
}
