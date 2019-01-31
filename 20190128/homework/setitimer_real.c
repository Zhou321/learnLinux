#include <func.h>

void sigfunc(int sigNum)
{
    time_t now;
    now=time(NULL);
    printf("%s\n",ctime(&now));
}

int main()
{
    signal(SIGALRM,sigfunc);
    sigfunc(0); 
    struct itimerval t;
    memset(&t,0,sizeof(t));
    t.it_value.tv_sec=3;
    t.it_interval.tv_sec=2;
    int ret=setitimer(ITIMER_REAL,&t,NULL);
    if(-1==ret)
    {
        perror("setitimer");
        return -1;
    }
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    return 0;
}

