#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("./xxx [fifoname]\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    int len;
    char buff[4096];
    int i = 0;
    while(1)
    {
        sprintf(buff, "Hello world %d\n", i++);
        write(fd, buff, strlen(buff));
        sleep(1);
    }
    close(fd);

    return 0;
}
