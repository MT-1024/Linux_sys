#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        //child
        printf("--child,my parent=%d, ging to sleep 10s\n", getppid());
        printf("---------------child die ----------------------\n");
    }
    else if(pid > 0)
    {
        //father
        sleep(10);
        printf("I am parent, pid=%d, myson = %d\n", getpid(), pid);
    }
    else
    {
        perror("fork error");
        return 1;
    }
    return 0;
}
