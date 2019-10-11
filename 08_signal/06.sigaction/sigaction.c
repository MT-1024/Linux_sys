//sigaction()是posix标准的捕获函数, signal()是ansi标准
//用sigaction()实现信号捕捉
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_catch(int signo)
{
    printf("have catch the signal:%d\n", signo);
}

int main(int argc, char * argv[])
{
    struct sigaction act, oldact;
    act.sa_handler = sig_catch; //捕获信号后，执行相应函数（动作）
    sigemptyset(&act.sa_mask); //清空sa_mask,当sig_catch工作时，sa_mask才有效
    act.sa_flags = 0; //默认值
    int ret = sigaction(SIGINT, &act, &oldact);    
    if(-1 == ret)
    {
        perror("sigaction error");
        return -1;
    }
    //死循环保证程序一直运行，通过键盘发送ctrl + c SIGINT信号，可以看到效果.
    while(1);

    return 0;
}
