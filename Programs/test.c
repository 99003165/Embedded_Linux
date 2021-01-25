#include <stdio.h>
#include "func.h"

int main()
{
	int a,b,c,d;
	a=10, b=20;
	c = sum(a,b);
	d = square(a);

	printf("Sum: %d, Square: %d",c,d);
	return 0;
}
	
