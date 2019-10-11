#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

//打印未决信号集
void print_set(sigset_t *set)
{
    for(int i = 1; i < 32; ++i)
    {
        if(sigismember(set, i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

int main()
{
    //myset是自定义set, 传入参数
    //originset是传出参数，用于保阻塞信号集修改之前的状态
    sigset_t myset, originset;
    sigset_t pedset;
    //sigempryset()先将自定义信号集清空
    sigemptyset(&myset);
    //sigaddset()将自定义信号集的相应位设置阻塞
    sigaddset(&myset, SIGINT);

    //sigprocmask()将自定义信号集和pcb中的阻塞信号集(mask)做或操作, 从而影响pcb的阻塞信号集
    int ret = sigprocmask(SIG_BLOCK, &myset, &originset);
    if(-1 == ret)
    {
        perror("sigprocmask error");
        return -1;
    }

    //查看pcb的未决信号集(pedding set)
    //ctrl + c 会发送 SIGINT到未决信号集
    while(1)
    {
        ret = sigpending(&pedset);
        if(-1 == ret)
        {
            perror("sigpending error");
            return -1;
        }
        print_set(&pedset); 
        sleep(1);
    }
    return 0;
}
