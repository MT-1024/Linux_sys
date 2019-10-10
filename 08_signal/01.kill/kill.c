#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char * argv[])
{
    int pid = fork();

    if(pid > 0)
    {
        printf("---parent---, pid = %d\n", getpid());
        printf("parent fork pid=%d\n",pid);
        while(1);
    }

    else if(pid == 0)
    {
        printf("---child---, child pid = %d, ppid = %d\n", getpid(), getppid());
        printf("fork pid=%d\n", pid);
        sleep(2);
        //子进程发送SIGKILL信号给父进程,结束父进程
        kill(0, SIGKILL);
    }

    return 0;
}
