#include <func.h>

void timeConvert(struct tm stTm)
{
    char chWeek[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    char chMonth[12][4]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    printf("%s %s %d %d:%d:%d %d\n",chWeek[stTm.tm_wday],chMonth[stTm.tm_mon],stTm.tm_mday,stTm.tm_hour+8,
           stTm.tm_min,stTm.tm_sec,stTm.tm_year+1900);
}

void* threadFunc(void *p)
{
    time_t timeti=time(NULL);
    struct tm stTm;
    gmtime_r(&timeti,&stTm);
    timeConvert(stTm);
    sleep(5);
    timeConvert(stTm);
}

int main()
{
    pthread_t thrid;
    int ret=pthread_create(&thrid,NULL,threadFunc,NULL);
    if(ret!=0)
    {
        printf("fail to pthread_create\n");
        return -1;
    }
    sleep(2);
    time_t timeti=time(NULL);
    struct tm stTm;
    gmtime_r(&timeti,&stTm);
    timeConvert(stTm);
    pthread_join(thrid,NULL);
    return 0;
}

