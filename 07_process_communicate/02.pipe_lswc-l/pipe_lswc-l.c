//ls | wc -l
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char * argv[])
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }


    pid_t pid = fork();
    if(pid > 0)
    {
        //father
        //father : both read and write end of pipe are open by default
        //father need to close the read end of pipe
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        close(fd[1]);
        //保证父进程后结束，有利于子进程先打印
    }
    else if(pid == 0)
    {
        //child
        //chlid : both read and write end of pipe are open by default
        //child need to close the write end of the pipe
        close(fd[1]);
        //wc 默认从标准输入读
        //wc 现在需要从管道读数据
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        close(fd[0]);
    }
    return 0;
}

