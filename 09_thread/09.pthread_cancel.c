//pthread_cancel终止子线程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * threadaction(void * arg)
{
    while(1)
    {
        printf("thread: pid=%d, tid=%lu\n",getpid(), pthread_self());
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    //获取线程ID

    //创建线程
    int ret = pthread_create(&tid, NULL, threadaction, NULL);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }


    printf("main: pid=%d, tid=%lu\n",getpid(), pthread_self());

    sleep(3);

    ret = pthread_cancel(tid); //终止子线程
    if(0 != ret)
    {
        fprintf(stderr, "pthread_cancel error : %s\n", strerror(ret));
        exit(1);
    }

    while(1);

    //主线程退出
    pthread_exit((void *)0);
}
