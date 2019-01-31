#include "func.h"

int main(int argc,char **argv)
{
	args_check(argc,2);
	int fd = open(argv[1],O_WRONLY | O_CREAT);
	lseek(fd,1000,SEEK_SET);
	write(fd,"1",1);
	close(fd);
	return 0;
}
