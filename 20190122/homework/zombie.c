#include "func.h"

int main()
{
	int ret = fork();
	if(!ret)
	{
		printf("son uid=%d\n",getpid());
		exit(0);
	}else{
		printf("parent uid=%d\n",getpid());
		while(1);
	}
	return 0;
}
