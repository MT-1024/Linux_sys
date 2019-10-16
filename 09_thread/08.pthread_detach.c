//线程分离函数
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

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
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }

    //设置子线程分离
    //线程终止，会自动清理PCB，无需回收
    ret = pthread_detach(tid);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_detach error : %s\n", strerror(ret));
        exit(1);
    }

    sleep(1);

    //子线程已经分离，会自动清理PCB，不需要再在主线程中调用pthread_join回收子线程
    ret = pthread_join(tid, NULL);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_join error : %s\n", strerror(ret));
        exit(1);
    }
    
    //如果没有sleep函数，主线程结束，系统回收进程地址空间，而子线程是与主线程共享地址空间的
    sleep(1);
    return 0;
}
