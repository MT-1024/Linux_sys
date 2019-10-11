#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sig_catch(int signo)
{
    printf("have catch signal %d\n", signo);
}

int main()
{
    //祖册告诉内核：捕获SIGINT信号，执行相应函数
    //第二个参数是函数指针类型，传自定义的函数名即可
    signal(SIGINT, sig_catch);
    while(1);
    return 0;
}
