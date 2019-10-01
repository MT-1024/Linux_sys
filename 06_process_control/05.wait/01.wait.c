#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char * argv[])
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if(pid > 0)
    {
        //father
        printf("father: pid=[%d], fpid=[%d]\n", getpid(), getppid());
        int status;
        pid_t wpid = wait(&status);
        printf("wpid=[%d]\n", wpid);
        if(WIFEXITED(status))
        {
            printf("chlid exit normal, status=[%d]\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status))
        {
            printf("child killed by signal, signal_NO==[%d]\n", WTERMSIG(status));
        }
    }
    else if(pid == 0)
    {
        //child
        printf("child: pid=[%d], fpid=[%d]\n", getpid(), getppid());
        sleep(10);
    }

    return 0;
}
