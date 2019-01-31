#include <func.h>
void sigHandler(int sigNum,siginfo_t *p,void *p1)
{
    printf("enter signal %d\n",sigNum);
}

int main()
{
    sigset_t sigBlockSet;
    sigset_t sigBloRes;
    sigemptyset(&sigBlockSet);
    sigaddset(&sigBlockSet,SIGINT);
    sigprocmask(SIG_BLOCK,&sigBlockSet,NULL);
    struct sigaction act;
    act.sa_sigaction=sigHandler;
    act.sa_flags=SA_SIGINFO;
    sigaction(SIGINT,&act,NULL);
    sleep(5);
    sigpending(&sigBloRes);
    if(sigismember(&sigBloRes,SIGINT))
    {
        printf("Signals are being blocked\n");
    }else{
        printf("no signals are being blocked\n");
    }
    sigprocmask(SIG_UNBLOCK,&sigBlockSet,NULL);
    return 0;
}

