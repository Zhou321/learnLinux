#include "func.h"

int main()
{
	int ret = fork();
	if(!ret)
	{
		printf("son gid=%d\n",getpid());
		exit(0);
	}else{
		printf("parent gid=%d\n",getpid());
		int pid = wait(NULL);
		printf("return son pid=%d\n",pid);
	}
	return 0;
}
