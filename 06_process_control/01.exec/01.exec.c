#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        //子进程
        /* execlp("ls", "ls", "-a", "-l", NULL); */
        execl("./hello", "./hello", NULL);
        perror("exec error");
        exit(1);
    }
    else if(pid > 0)
    {
        //父进程
        //父进程如果不睡眠，如果父进程先终止，终端会显示bash
        sleep(1);
        printf("parent's pid : %d\n", getpid());
    }
    return 0;
}
