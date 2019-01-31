#include <func.h>

int main()
{
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    pthread_mutex_t *shareLock;
    char *buf=(char*)shmat(shmid,NULL,0);
    char *pTmp;
    if((char*)-1!=buf)
    {
        shareLock=(pthread_mutex_t*)buf;
        while(1)
        {
            pthread_mutex_lock(shareLock);
            pTmp=(char*)(((pthread_mutex_t*)buf)+1);
            printf("p[0]=%c\n",pTmp[0]); 
            if(pTmp[0]=='#')
            {
                printf("exit\n");
                exit(0);
            }else if(pTmp[1]!=0)
            {
                printf("%s\n",pTmp+1);
                memset(buf,0,4096); 
            }
            pthread_mutex_unlock(shareLock);
        }
        return 0;
    }
}
