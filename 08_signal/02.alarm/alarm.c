#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    //1秒后，alarm函数的定时器结束，会发送SIGALRM信号给本程序，终止本程序
    alarm(1);
    
    for(int i = 0; ; i++)
    {
        printf("%d\n", i);
    }

    return 0;
}
