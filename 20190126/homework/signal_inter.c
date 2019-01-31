#include <func.h>


void sigfunc(int sigNum)
{
    printf("before sleep is signal %d\n",sigNum);
    sleep(3); 
    printf("after sleep is signal %d\n",sigNum);
}
int main()
{
    signal(SIGINT,sigfunc);
    signal(SIGQUIT,sigfunc);
    while(1);
    return 0;
}

