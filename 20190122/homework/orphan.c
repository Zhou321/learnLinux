#include "func.h"

int main()
{
	int ret = fork();
	if(!ret)
	{
		printf("son uid=%d\n",getpid());
		while(1);
	}else{
		printf("parent uid=%d\n",getpid());
		exit(0);
	}
	return 0;
}
