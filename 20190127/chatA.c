#include <func.h>
int semid;
pthread_mutex_t * sharedLock;
char *buf=NULL;
void sigHandler(int sigNum,siginfo_t *p,void *p1)
{
    memset(buf,0,4096);
    sharedLock = (pthread_mutex_t*)buf;
    //pthread_mutex_lock(sharedLock);
    //char *pTmp=(char*)(((pthread_mutex_t*)buf)+1);
    memset(((pthread_mutex_t*)buf)+1,'#',1);
    //pTmp[0]=2; 
    //pthread_mutex_unlock(sharedLock);
    if(buf!=NULL && -1==shmdt(buf))
    {
        perror("fail to shmdt");
    }else{
        printf("del current shared memory\n");
        exit(0);
    }
}
int main(int argc, char **argv)
{
    args_check(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    struct sigaction act;
    act.sa_sigaction=sigHandler;
    act.sa_flags=SA_SIGINFO;
    sigaction(SIGINT,&act,NULL);
    pthread_mutexattr_t ma;
    if(-1==fdr)
    {
        perror("fdr error");
        return -1;
    }
    int fdw=open(argv[2],O_WRONLY);
    if(-1==fdw)
    {
        perror("fdw error");
        return -1;
    }
    semid=semget(1000,1,IPC_CREAT|0600); 
    if(-1==semid)
    {
        perror("fail to get semid");
        return -1;
    }
    printf("chatA:\n");
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    buf = (char*)shmat(shmid,NULL,0);
    pthread_mutexattr_init(&ma);
    pthread_mutexattr_setpshared(&ma, PTHREAD_PROCESS_SHARED);
    pthread_mutexattr_setrobust(&ma, PTHREAD_MUTEX_ROBUST);
    char stdBuf[128]={0};
    while(1)
    {
        fd_set rdset;
        int ret;
        FD_ZERO(&rdset);
        FD_SET(0,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(0<ret)
        {
            if(FD_ISSET(fdr,&rdset))
            {
                memset(buf,0,4096);
                sharedLock = (pthread_mutex_t*)buf;
                pthread_mutex_init(sharedLock,&ma);
                pthread_mutex_lock(sharedLock);
                ret=read(fdr,((pthread_mutex_t*)buf)+2,4087);
                pthread_mutex_unlock(sharedLock);
                if(-1==ret)
                {
                    perror("fail to read pipe");
                    break;
                }
            }
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(stdBuf,0,sizeof(stdBuf));
                ret=read(STDIN_FILENO,stdBuf,sizeof(stdBuf));
                if(-1==ret)
                {
                    perror("fail to read stdin");
                    break;
                }
                write(fdw,stdBuf,strlen(stdBuf)-1);
            }
        }
    }
    return 0;
}

