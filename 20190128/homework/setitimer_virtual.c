#include <func.h>

void sigfunc(int sigNum)
{
    time_t now;
    now=time(NULL);
    printf("%s\n",ctime(&now));
}

int main()
{
    signal(SIGVTALRM,sigfunc);
    sigfunc(0); 
    struct itimerval t;
    memset(&t,0,sizeof(t));
    t.it_value.tv_sec=3;
    t.it_interval.tv_sec=2;
    int ret=setitimer(ITIMER_VIRTUAL,&t,NULL);
    if(-1==ret)
    {
        perror("setitimer");
        return -1;
    }
    sleep(5);
    while(1);
    return 0;
}

