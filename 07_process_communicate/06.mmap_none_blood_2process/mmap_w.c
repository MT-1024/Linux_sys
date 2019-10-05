#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>

void sys_err(const char * str)
{
    perror(str);
    exit(1);
}
struct student
{
    int id;
    char name[256];
    int age;
};
typedef struct student Student;

int main(int argc, char * argv[])
{
    Student stu = {1, "xiaoming", 20};
    Student * p;
    int fd = open("buffer_mmap.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);    
    if(-1 == fd)
    {
        sys_err("open error");
    }
    ftruncate(fd, sizeof(stu));
    
    p = (Student *)mmap(NULL, sizeof(stu), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == p)
    {
        sys_err("mmap error");
    }
    close(fd);
    while(1)
    {
        memcpy(p, &stu, sizeof(stu));
        ++stu.id;
        sleep(1);
    }
    
    munmap(p, sizeof(stu));
    

    return 0;
}
