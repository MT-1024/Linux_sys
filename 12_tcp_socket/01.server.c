#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 8089

void sys_err(const char * str)
{
    perror(str);
    exit(1);
}
int main()
{
    //1.创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == lfd)
    {
        sys_err("create socket error\n"); 
    }

    //2.绑定IP和端口到socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    int ret = bind(lfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(-1 == ret)
    {
        sys_err("bind error\n");
    }

    //3.设置服务器同时最大连接数
    listen(lfd, 128);
    if(-1 == ret)
    {
        sys_err("listen error\n");
    }

    //4.设置阻塞，等待客户端建立连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connect_fd = accept(lfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if(-1 == connect_fd)
    {
        sys_err("accept error\n");
    }

    char client_ip[1024];
    printf("client IP:%s , client PORT:%d\n", 
           inet_ntop(AF_INET, (void *)&client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip)), 
           ntohs(client_addr.sin_port));

    //读客户端来的数据
    char buf[4096];
    while(1)
    {
        ret = read(connect_fd, buf, sizeof(buf)); 
        write(STDOUT_FILENO, buf, ret);

        //将数据转化为大写
        for(int i = 0; i < ret; ++i) 
        {
            buf[i] = toupper(buf[i]);
        }

        //写回buf
        write(connect_fd, buf, ret); 

    }
    
    close(lfd);
    close(connect_fd);

    return 0;
}
