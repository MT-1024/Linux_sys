#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    printf("before fork 1\n");
    printf("before fork 2\n");
    printf("before fork 3\n");
    printf("before fork 4\n");

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        //子进程
        printf("pid=%d , child's fork()--->: %d , %d\n", pid, getpid(), getppid());
    }
    else if(pid > 0)
    {
        //父进程
        //执行本程序时，操作系统执行fork(),将bash的子进程分配给本程序,自己写的程序都是
        //bash的子程序
        printf("pid=%d , parent's fork()--->: %d , %d\n",pid ,getpid(), getppid());
    }
    printf("------------end of file------------------\n");
    return 0;
}
