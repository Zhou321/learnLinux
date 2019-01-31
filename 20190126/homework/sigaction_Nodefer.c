#include <func.h>

void signalHandler(int sigNum, siginfo_t *p,void *p1)
{
    printf("signal%d is coming\n",sigNum);
}
int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    act.sa_sigaction=signalHandler;
    int ret = sigaction(SIGINT,&act,NULL);
    if(-1==ret)
    {
        perror("fail to sigaction");
        return -1;
    }
    while(1);
    return 0;
}

