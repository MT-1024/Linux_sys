//主线程和子线程共享全局变量
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int var = 10;

void * pthreadaction(void * arg)
{
    var = 20;
    printf("thread : var = %d\n", var);
    return NULL;
}
int main()
{
    printf("main thread global var = %d\n", var);
    
    pthread_t tid;
    pthread_create(&tid, NULL, pthreadaction, NULL);
    sleep(1);

    printf("after pthread_create change global var = %d\n", var);
    return 0;
}
