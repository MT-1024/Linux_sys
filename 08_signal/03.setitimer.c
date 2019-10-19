#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void func(int signo)
{
    printf("hello world!\n");
}

int main()
{
    struct itimerval newit, oldit;

    signal(SIGALRM, func);

    newit.it_value.tv_sec = 2;
    newit.it_value.tv_usec = 0;
    newit.it_interval.tv_sec = 5;
    newit.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &newit, &oldit) == -1)
    {
        perror("setitimer error");
        return -1;
    }
    
    //2秒后，setitimer会发送SIGALRM给signal()，signal()收到信号后会执行func()
    //5秒后，setitimer会再次发送SIGALRM给signal()，signal()收到信号后会执行func()
    //5s later, 循环
    while(1);

    return 0;
}
