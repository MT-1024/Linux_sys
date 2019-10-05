//mmap实现父子进程间通信
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc, char * argv[])
{
    int var = 0;
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }

    //拓展创建的空文件,以下2个等价于ftrucate()
    /* lseek(fd, 10, SEEK_END); */
    /* write(fd, "\0", 1); */

    ftruncate(fd, 4);
    int len = lseek(fd, 0, SEEK_END);
    
    int * p = (int *) mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }
    //映射区建立完毕，可以关闭文件
    close(fd);

    pid_t pid = fork();
    if(pid == 0)
    {
        //child
        *p = 100;
        var = 200;
        printf("---child---, *p=[%d], var=[%d]\n", *p, var);        
    }
    else if(pid > 0)
    {
        //father
        sleep(1);
        printf("---father---, *p=[%d], var=[%d]\n", *p, var);        
        //回收子进程
        wait(NULL);
    }

    return 0;
}
