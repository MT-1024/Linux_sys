#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    pid_t pid, wpid;
    pid = fork();

    int status;

    if(pid == 0)
    {
        //child process
        printf("-----child process: going to sleep,  my pid = %d\n ", getpid());
        sleep(10);
        printf("-------child die------------\n");
        return 73;
    }
    else if(pid > 0)
    {
        //father process
        // father process will wait child process until child die,then will recycle cild
        printf("------father process is waiting child die\n");
        wpid = wait(&status);
        if(wpid == -1)
        {
            perror("wait error");
            return 1;
        }
        if(WIFEXITED(status))  //为真，说明进程正常终止
        {
            printf("child exit return with %d\n", WEXITSTATUS(status));  //获取子进程结束时的 return 值
        };
        if(WIFSIGNALED(status))  //为真，说明子进程被信号终止
        {
            printf("child killed with signal %d\n", WTERMSIG(status));
        }
        printf("recycle process pid=%d\n", wpid);
    }
    else
    {
        perror("fork error");
        return 1;
    }

    return 0;
}
