#include <func.h>

void *pthreadFunc(void *p)
{
    printf("child thread\n");
}

int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthreadFunc,NULL);
    if(-1==ret)
    {
        printf("fail to pthread_create\n");
        return -1;
    }
    int iRet=0;
    pthread_cancel(pthid);
    ret=pthread_join(pthid,(void**)&iRet);
    if(ret!=0)
    {
        printf("fail to pthread_join\n");
        return -1;
    }
    printf("main thread: chile thread exit value is %d\n",iRet);
    return 0;
}

