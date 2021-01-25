#include<unistd.h>
#include<stdio.h>
#include <string.h>

#define __NR_testecho 401

int main() 
{
	int ret;
	char *src ="New World";
		
	size_t len = strlen(src) - 1;
	char dest[64];
	ret = syscall(__NR_testecho,src,dest,len);
	if(ret<0)
		perror("Echo Call");
	else 
		printf("the message :%s\n", dest);
	return 0;
}
