#include <func.h>

void sigHandler(int iSignNo)
{
    printf("before: sign no:%d\n",iSignNo);
    sleep(3);
    printf("after: sign no:%d\n",iSignNo);
}

int main()
{
    signal(SIGINT,sigHandler);
    signal(SIGQUIT,sigHandler);
    while(1);
    return 0;
}

