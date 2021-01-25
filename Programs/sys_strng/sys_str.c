#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define __NR_mytestcall2 400

int main() 
{
	int ret;
	char *str ="New World";
	size_t len = strlen(str);
	ret = syscall(__NR_mytestcall2,str,len);
	if(ret<0)
		perror("String Call");
	return 0;
}
