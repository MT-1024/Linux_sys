#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("child process pid is %d\n", getpid());
        printf("group id of child is %d\n", getpgid(0));
        printf("session id of chlid is %d\n", getsid(0));

        sleep(10);
        setsid(); //子进程非组长进程，故其成为新会话首进程，且成为组长进程。

        printf("after changed:\n");

        printf("child process pid is %d\n", getpid());
        printf("group id of child is %d\n", getpgid(0));
        printf("session id of chlid is %d\n", getsid(0));

        sleep(20);
        exit(0);
    }
    return 0;
}
