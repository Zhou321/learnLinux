#include <func.h>

void sig3Handler(int iSigNum,siginfo_t *p, void *p1)
{
    printf("before sleep is signal %d\n",iSigNum);
    sleep(3);
    sigset_t setPend;
    sigpending(&setPend);
    if(sigismember(&setPend,SIGQUIT))
    {
        printf("SIGQUIT is in pending set\n");
    }else{
        printf("SIGQUIT is not in pending set\n");
            }
    printf("after sleep is signal %d\n",iSigNum);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_sigaction = sig3Handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

