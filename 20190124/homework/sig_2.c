#include <func.h>

void sigHandler(int iSignNo)
{
    printf("capture sign no:%d\n",iSignNo);
}

int main()
{
    signal(SIGINT,sigHandler);
    while(1);
    return 0;
}

