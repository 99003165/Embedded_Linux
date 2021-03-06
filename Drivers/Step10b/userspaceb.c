#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#define	MAX_SIZE 	1024
#define	IOC_MAGIC 	'p'
#define	MY_IOCTL_LEN	_IO(IOC_MAGIC, 1)
#define	MY_IOCTL_AVAIL	_IO(IOC_MAGIC, 2)
#define	MY_IOCTL_RESET	_IO(IOC_MAGIC, 3)
struct pseudo_stat {
	int len;
	int avail;
};

#define	MY_IOCTL_PSTAT	_IOR(IOC_MAGIC, 4, struct pseudo_stat)

int main()
{	
	int fd, ret;
	struct pseudo_stat stat;
	fd = open("/dev/psample2", O_RDWR);

	if(fd<0) 
	{
		perror("open");
		exit(1);
	}

	/*ret=ioctl(fd, MY_IOCTL_LEN);
	if(ret<0)
	{
		perror("ioctl");
		exit(3);
	}

	ret=ioctl(fd, MY_IOCTL_AVAIL);
	if(ret<0)
	{
		perror("ioctl");
		exit(3);
	}

	ret=ioctl(fd, MY_IOCTL_RESET);
	if(ret<0) 
	{
		perror("ioctl");
		exit(3);
	}*/
	
	ret=ioctl(fd, MY_IOCTL_PSTAT, &stat);
	if(ret<0) 
	{
		perror("ioctl");
		exit(4);
	}
	printf("Len=%d, Available=%d", stat.len, stat.avail);
	close(fd);
}
