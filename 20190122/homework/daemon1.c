#include "func.h"

void daemon1()
{
	int i=0;
	// exit the parent process
	if(fork()){
		exit(0);
	}
	printf("pid=%d\n",getpid());
	setsid();
	chdir("/");
	umask(0);
	for(;i<3;i++){
		close(i);
	}
}

int main()
{
	daemon1();
	int fd = open("/tmp/log",O_RDWR);
	char buf[128]={0};
	strcpy(buf,"I have sleep 1s");
	while(1)
	{
		write(fd,buf,15);
		fsync(fd);
		sleep(1);
	}
	return 0;
}

