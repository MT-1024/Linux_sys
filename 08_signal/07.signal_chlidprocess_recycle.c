//利用SIGCHLD实现子进程回收
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void catch_chlid(int signo)
{
    pid_t wpid;
    while((wpid = wait(NULL)) != -1)
    {
        printf("---catch chlid id %d\n", wpid);
    }
    printf("SIGNO:%d\n", signo);
}
int main()
{
    pid_t pid;
    int i;
    for(i = 0; i < 5; i++)
    {
        if((pid = fork()) == 0)
        {
            break;
        }
    }
    if(5 == i)
    {
        struct sigaction act, originact;

        act.sa_handler = catch_chlid;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD, &act, &originact);

        printf("---parent pid=%d\n", getpid()); 
        sleep(1);
    }
    else
    {
        printf("---child pid=%d\n", getpid());
    }
    return 0;
}
