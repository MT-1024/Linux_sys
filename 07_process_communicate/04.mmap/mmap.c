#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }

    //拓展创建的空文件,以下2个等价于ftrucate()
    /* lseek(fd, 10, SEEK_END); */
    /* write(fd, "\0", 1); */

    ftruncate(fd, 20);
    int len = lseek(fd, 0, SEEK_END);
    
    char * p = (char *) mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }

    close(fd);

    strcpy(p, "Hello World!");
    printf("[%s]\n", p);
    
    //回收映射区
    int ret = munmap(p, len);
    if(-1 == ret)
    {
        perror("munmap error");
    }

    return 0;
}
