#include <func.h>

void *pthreadFunc(void *p)
{
    printf("child thread: %d\n",*(int*)p);
    pthread_exit((void*)2);
}

int main()
{
    pthread_t pthid;
    int iArg=1;
    int ret=pthread_create(&pthid,NULL,pthreadFunc,&iArg);
    if(-1==ret)
    {
        printf("fail to pthread_create\n");
        return -1;
    }
    int iRet=0;
    ret=pthread_join(pthid,(void**)&iRet);
    if(ret!=0)
    {
        printf("fail to pthread_join\n");
        return -1;
    }
    printf("main thread: chile thread exit value is %d\n",iRet);
    return 0;
}

