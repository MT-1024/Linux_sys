#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main()
{
    pthread_t tid;
    //获取线程ID
    tid = pthread_self();    
    printf("main: pid=%d, tid=%lu\n",getpid(), tid);
     

    return 0;
}
