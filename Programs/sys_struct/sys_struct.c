#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define __NR_structcall 402

struct sample {
int x;
int y;
int z;
};

int main() 
{
	int ret;
	struct sample s1;
	s1.x=10; 
	s1.y=20; 
	s1.z=30;
	ret = syscall(__NR_structcall,&s1);
	if(ret<0)
		perror("String Call");
	return 0;
}
