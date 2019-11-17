#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 8089 

void * sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char * argv[])
{
    //1.创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == lfd)
    {
        sys_err("create socket error\n");        
    }
    
    //2.connect连接服务端
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    /* server_addr.sin_addr.s_addr = htonl(INADDR_ANY); */
    inet_pton(AF_INET, "127.0.0.1", (void *)&server_addr.sin_addr.s_addr);
    int ret = connect(lfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret == -1)
    {
        sys_err("client connect error\n");        
    }


    char buff[1024] = {0};
    while(1)
    {
        scanf("%s", buff);
        write(lfd, buff, strlen(buff));
        ret = read(lfd, (void *)buff, sizeof(buff));
        write(STDOUT_FILENO, (void *)buff, ret);
    }

    close(lfd);
    return 0;
}
