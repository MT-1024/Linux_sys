#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        //child process
        while(1)
        {
            printf("this is child process, my parent pid=%d\n", getppid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        //father process
        printf("this is parent process, my pid is=%d\n", getpid());
        sleep(9);
        printf("-------parent going to die---------------\n");
    }
    else
    {
        perror("fork");
        return 1;
    }


    return 0;
}
