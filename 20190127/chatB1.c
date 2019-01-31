#include <func.h>

int main()
{
    int shmid=shmget(1001,4096,IPC_CREAT|0600);
    pthread_mutex_t *shareLock;
    char *buf=(char*)shmat(shmid,NULL,0);
    char *pTmp;
    if((char*)-1!=buf)
    {
        shareLock=(pthread_mutex_t*)buf;
        while(1)
        {
            pTmp=(char*)(((pthread_mutex_t*)buf)+1);
            if(pTmp[0]!=0)
            {
                pthread_mutex_lock(shareLock);
                printf("%s\n",pTmp);
                memset(buf,0,4096); 
                pthread_mutex_unlock(shareLock);
            }
        }
    }
    return 0;
}

