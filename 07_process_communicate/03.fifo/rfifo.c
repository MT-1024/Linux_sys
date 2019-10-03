#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("./xxx [fifoname]\n");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    int len;
    char buff[4096];
    while(1)
    {
        len = read(fd, buff, sizeof(buff));
        write(STDOUT_FILENO, buff, len);
        sleep(1);
    }
    close(fd);

    return 0;
}
