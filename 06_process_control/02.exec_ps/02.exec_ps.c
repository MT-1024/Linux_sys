#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{

    int fd = open("ps.log", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open ps.log error");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO);
    
    execlp("ps", "ps", "aux", NULL);
    perror("execlp error");

    close(fd);
    return 0;
}
