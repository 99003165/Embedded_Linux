#include<unistd.h>
#include<stdio.h>

#define __NR_testcall 399

int main() 
{
	int ret;
	ret = syscall(__NR_testcall,3,2);
	if(ret<0)
		perror("SumCall");
	return 0;
}
