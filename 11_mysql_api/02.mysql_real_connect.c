#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysql/mysql.h"

int main()
{
    //MYSQL *mysql_init(MYSQL *mysql)
    //mysql初始化 
    MYSQL *msq = mysql_init(NULL);
    if(NULL == msq)
    {
        printf("mysql init error\n");
    }

    printf("mysql init success\n");
    
    MYSQL *conn = mysql_real_connect(msq, "192.168.0.115", "wjf", "321284", "scott", 3306, NULL, 0);
    if(conn == NULL)
    {
        printf("mysql connect error:[%s]\n", mysql_error(msq));
    }
    printf("mysql connect success\n");
    if(conn == msq)
    {
        printf("conn and msq is same\n");
    }
    //释放资源
    mysql_close(msq);
    return 0;
}
