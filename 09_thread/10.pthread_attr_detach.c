//设置线程默认分离态
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
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

    //初始化线程属性结构体
    pthread_attr_t attr;
    int ret = pthread_attr_init(&attr);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_attr_init error:%s\n", strerror(ret));
        exit(1);
    }


    //设置默认线程属性为分离属性
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
        exit(1);
    }


    //创建线程
    ret = pthread_create(&tid, &attr, threadaction, NULL);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
        exit(1);
    }

    //取消默认线程属性为分离属性
    ret = pthread_attr_destroy(&attr);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_attr_destroy error:%s\n", strerror(ret));
        exit(1);
    }

    //保证子线程运行结束
    sleep(1); //等待子线程死亡,实际pthread_join()也会等待子线程死亡

    //测试线程是否是分离态，如果是，则pthread_join()回收失败
    ret = pthread_join(tid, NULL);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_join error:%s\n", strerror(ret));
        exit(1);
    }



    //如果没有sleep函数，主线程结束，系统回收进程地址空间，而子线程是与主线程共享地址空间的
    sleep(1);
    return 0;
}
