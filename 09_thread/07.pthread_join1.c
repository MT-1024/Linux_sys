//创建、回收子线程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * pthreadaction(void *arg)
{
    return (void *)74;
}
int main()
{
    pthread_t tid;
    int * pthread_return_value;
    int ret = pthread_create(&tid, NULL, pthreadaction, NULL);
    if(0 != ret)
    {
        perror("pthread_create error");
        exit(1);
    }

    ret = pthread_join(tid, (void **)&pthread_return_value);
    if(0 != ret)
    {
        perror("pthread_create error");
        exit(1);
    }
    printf("child thread exit with %d\n", (int *)pthread_return_value);
    sleep(1);
    return 0;
}
