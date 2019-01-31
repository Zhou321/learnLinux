#include <func.h>

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    long lTicketCounts;
}threadinfo;

void *threadFunc1(void *p)
{
    threadinfo *pInfo=(threadinfo*)p;
    while(1)
    {
        pthread_mutex_lock(&pInfo->mutex);
        if(pInfo->lTicketCounts>0)
        {
            printf("Window 1: %ld\n",pInfo->lTicketCounts);
            pInfo->lTicketCounts--;
            if(0==pInfo->lTicketCounts)
            {
                pthread_cond_signal(&pInfo->cond);
            }
            printf("Window 1: sells ok %ld\n",pInfo->lTicketCounts);
            pthread_mutex_unlock(&pInfo->mutex);
        }else{
            pthread_mutex_unlock(&pInfo->mutex);
            break;
        }
    }
}
void *threadFunc2(void *p)
{
    threadinfo *pInfo=(threadinfo*)p;
    while(1)
    {
        pthread_mutex_lock(&pInfo->mutex);
        if(pInfo->lTicketCounts>0)
        {
            printf("Window 2: %ld\n",pInfo->lTicketCounts);
            pInfo->lTicketCounts--;
            if(0==pInfo->lTicketCounts)
            {
                pthread_cond_signal(&pInfo->cond);
            }
            printf("Window 2: sells ok %ld\n",pInfo->lTicketCounts);
            pthread_mutex_unlock(&pInfo->mutex);
        }else{
            pthread_mutex_unlock(&pInfo->mutex);
            break;
        }
    }
}
void *resetTickets(void *p)
{
    threadinfo *pInfo=(threadinfo*)p;
    pthread_mutex_lock(&pInfo->mutex);
    if(0<pInfo->lTicketCounts)
    {
        pthread_cond_wait(&pInfo->cond,&pInfo->mutex);
        pInfo->lTicketCounts=10;
    }
    pthread_mutex_unlock(&pInfo->mutex);
    pthread_exit(NULL);
}

int main()
{
    threadinfo thrInfo;
    pthread_t thId1,thId2,thId3;
    int ret;
    ret=pthread_cond_init(&thrInfo.cond,NULL);
    if(ret!=0)
    {
        printf("fail to cond init\n");
        return -1;
    }
    ret=pthread_mutex_init(&thrInfo.mutex,NULL);
    if(ret!=0)
    {
        printf("fail to mutex init\n");
        return -1;
    }
    thrInfo.lTicketCounts=20;
    pthread_create(&thId1,NULL,threadFunc1,&thrInfo);
    pthread_create(&thId2,NULL,threadFunc2,&thrInfo);
    pthread_create(&thId3,NULL,resetTickets,&thrInfo);
    pthread_join(thId1,NULL);
    pthread_join(thId2,NULL);
    pthread_join(thId3,NULL);
    return 0;
}

