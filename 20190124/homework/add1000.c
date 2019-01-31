#include <func.h>

#define N 10000000
int main()
{
	int semAid = semget(1000,1,IPC_CREAT|0600);
	if(-1==semAid)
	{
		perror("fail to semget");
		return -1;
	}
	int ret = semctl(semAid,0,SETVAL,1);
	if(-1==ret)
	{
		perror("fail to ret");
		return -1;
	}
	int shmid = shmget(1000,4096,IPC_CREAT|0600);
	int *p = (int*)shmat(shmid,NULL,0);
	p[0]=0;
	struct sembuf sopp,sopv;
	sopp.sem_num = 0;
	sopp.sem_flg = SEM_UNDO;
	sopp.sem_op = -1;
	sopv.sem_num = 0;
	sopv.sem_flg = SEM_UNDO;
	sopv.sem_op = 1;
	int i;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			semop(semAid,&sopp,1);
			p[0]+=1;
			semop(semAid,&sopv,1);
		}
	}else{
		for(i=0;i<N;i++)
		{
			semop(semAid,&sopp,1);
			p[0]+=1;
			semop(semAid,&sopv,1);
		}
		wait(NULL);
		printf("%d\n",p[0]);
	}	
	return 0;
}
