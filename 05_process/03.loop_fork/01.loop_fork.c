#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{
    int i;
    pid_t pid;
    for(i = 0; i < 5; i++)
    {
        if(fork() == 0)
            break;
    }

    if( i== 5 )
    {
        printf("I'm parent\n");
    }
    else
    {
        printf("I'm %dth child\n", i+1);
    }        
    return 0;
}
