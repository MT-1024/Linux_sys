//循环创建多个子线程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * threadaction(void * arg)
{
    int i = (int)arg; //强转
    sleep(i);
    printf("this %dth thread: pid=%d, tid=%lu\n", i+1,getpid(), pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid;
    int i;
    int ret;

    //循环创建线程
    for(i = 0; i < 5; i++)
    {
        //传参采用值传递。借助强转
        ret = pthread_create(&tid, NULL, threadaction, (void *)i);
        if(0 != ret)
        {
            perror("pthread_create error");
            exit(1);
        }
    }
    //如果没有sleep函数，主线程结束，系统回收进程地址空间，而子线程是与主线程共享地址空间的
    sleep(i);
    printf("main: pid=%d, tid=%lu\n",getpid(), pthread_self());
    return 0;
}
