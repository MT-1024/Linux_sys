//线程之间设置全局互斥锁共享资源stdout
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

//定义一把全局互斥锁
pthread_mutex_t mymutex;

//子线程动作
void *pthread_action(void * arg)
{
    srand(time(NULL));
    while(1)
    {
        pthread_mutex_lock(&mymutex); //加锁
        printf("hello ");
        sleep(rand() % 3); //模拟操作长时间操作共享资源,导致CPU易主，产生与时间有关的错误
        printf("world\n");
        pthread_mutex_unlock(&mymutex); //解锁

        sleep(rand()%3);
    }
    return NULL;
}

int main()
{
    pthread_t tid; //用于保存待创建线程的ID
    srand(time(NULL));

    //初始化互斥锁
    int ret = pthread_mutex_init(&mymutex, NULL);
    if(0 != ret)
    {
        fprintf(stderr, "pthread_mutex_init error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid, NULL, pthread_action, NULL); //创建子线程
    if(0 != ret)
    {
        fprintf(stderr, "pthread_creat error:%s\n", strerror(ret));
        exit(1);
    }


    while(1)
    {
        pthread_mutex_lock(&mymutex); //加锁
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mymutex); //解锁

        sleep(rand() % 3);
    }


    pthread_join(tid, NULL); //等待子线程结束回收子线程
    

    pthread_mutex_destroy(&mymutex); //销毁互斥锁
    return 0;
}
