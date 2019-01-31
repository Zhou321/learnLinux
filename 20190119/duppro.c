#include "func.h"

int main()
{
	  //std out
	int fd = open("file1",O_RDWR|O_CREAT);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("\n");
	close(1);
	int fd2=dup(fd);
	close(fd);
	printf("hello\n");
	close(fd2);
}

