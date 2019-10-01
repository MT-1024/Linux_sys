//父进程调用waitpid()函数对结束的子进程回收
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char * argv[])
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if(pid > 0)
    {
        //父进程
        printf("father: pid==[%d]\n", getpid());
        int status;
        //-1代表等待任意子进程
        //WNOHANG:不阻塞
        //pid_t wpid = waitpid(-1, &status, 0);
        pid_t wpid = waitpid(-1, &status, WNOHANG); 
        printf("wpid==[%d]\n", wpid);
        if(wpid > 0)
        {
            if(WIFEXITED(status))
            {
                printf("child exit normal, status==[%d]\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("child killed by signal, signal.no==[%d]\n", WTERMSIG(status));
            }
        }
        else if(wpid == 0)
        {
            printf("child is running, wpid==[%d]\n", wpid);
        }
        else if(wpid == -1)
        {
            printf("no child is running, wpid==[%d]\n", wpid);
        }
    }
    else if(pid == 0)
    {
        //子进程
        printf("child: pid==[%d]\n", getpid());
        sleep(10);
    }


    return 0;    
}
