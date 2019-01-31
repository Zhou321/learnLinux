#include <func.h>

#define N 10000000
int main()
{
    int semAid = semget(1000,2,IPC_CREAT|0600);
    if(-1==semAid)
    {
        perror("fail to semget");
        return -1;
    }
    unsigned short arr[2]={10,0};
    int ret = semctl(semAid,0,SETALL,arr);
    if(-1==ret)
    {
        perror("fail to semctl");
        return -1;
    }
    struct sembuf sopp,sopv;
    if(!fork())
    {
        sopp.sem_num = 1;
        sopp.sem_flg = SEM_UNDO;
        sopp.sem_op = -1;
        sopv.sem_num = 0;
        sopv.sem_flg = SEM_UNDO;
        sopv.sem_op = 1;
        while(1)
        {
            printf("consumer: space=%d product=%d\n",semctl(semAid,0,GETVAL),semctl(semAid,1,GETVAL));
            semop(semAid,&sopp,1);
            printf("consume one\n");
            semop(semAid,&sopv,1);
            printf("consumer: space=%d product=%d\n\n",semctl(semAid,0,GETVAL),semctl(semAid,1,GETVAL));
            sleep(2);
        }
    }else{
        sopp.sem_num = 0;
        sopp.sem_flg = SEM_UNDO;
        sopp.sem_op = -1;
        sopv.sem_num = 1;
        sopv.sem_flg = SEM_UNDO;
        sopv.sem_op = 1;
        while(1)
        {
            printf("producer: space=%d product=%d\n\n",semctl(semAid,0,GETVAL),semctl(semAid,1,GETVAL));
            semop(semAid,&sopp,1);
            printf("produce one\n");
            semop(semAid,&sopv,1);
            printf("producer: space=%d product=%d\n\n",semctl(semAid,0,GETVAL),semctl(semAid,1,GETVAL));
            sleep(1);
        }
    }	
    return 0;
}
