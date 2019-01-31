#include <func.h>

int main()
{
	int shmid = shmget(1000,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget failed");
		return -1;
	}
	char *p = (char *)shmat(shmid,NULL,0);
	if((char *)-1==p)
	{
		perror("shmat failed");
		return -1;
	}
	if(!fork())
	{
		printf("son process:\n");
		puts(p);
	}else{
		strcpy(p,"How are you");
		wait(NULL);
	}
}
