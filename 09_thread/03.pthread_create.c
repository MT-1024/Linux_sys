#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * threadaction(void * arg)
{
    printf("thread: pid=%d, tid=%lu\n",getpid(), pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid;
    //获取线程ID
    printf("main: pid=%d, tid=%lu\n",getpid(), pthread_self());

    //创建线程
    int ret = pthread_create(&tid, NULL, threadaction, NULL);
    if(0 != ret)
    {
        perror("pthread_create error");
        exit(1);
    }
    
    //如果没有sleep函数，主线程结束，系统回收进程地址空间，而子线程是与主线程共享地址空间的
    sleep(1);
    return 0;
}
