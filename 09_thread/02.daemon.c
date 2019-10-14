//create Daemon
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    int ret;
    int fd;
    pid = fork();
    if(pid > 0)
    {
        exit(0); //father process exit
    }

    pid = setsid(); // create new session
    if(-1 == pid)
    {
        perror("setsid error");
        exit(1);
    }

    ret = chdir("/home/wjf"); //change working directory 
    if(-1 == ret)
    {
        perror("chdir error");
        exit(1);
    }

    umask(0022); //change file defatlt umask

    close(STDIN_FILENO);
    fd =  open("/dev/null", O_RDWR); //fd == 0
    if(-1 == fd)
    {
        perror("open error");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO); //重定向stdout stderr
    dup2(fd, STDERR_FILENO);

    while(1); //模拟守护进程业务

    return 0;
}
