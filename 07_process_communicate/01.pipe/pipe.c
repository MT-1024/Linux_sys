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

    char * str = "hello World!";
    char buff[1024]={0};

    pid_t pid = fork();
    if(pid > 0)
    {
        //father
        //father : both read and write end of pipe are open by default
        //father need to close the read end of pipe
        close(fd[0]);
        write(fd[1], str, strlen(str));
        close(fd[1]);
        //保证父进程后结束，有利于子进程先打印
        sleep(1);
    }
    else if(pid == 0)
    {
        //child
        //child need to close the write end of the pipe
        close(fd[1]);
        read(fd[0], buff, sizeof(buff));
        printf("child read pipe content=%s\n", buff);
        close(fd[0]);
    }
    return 0;
}

