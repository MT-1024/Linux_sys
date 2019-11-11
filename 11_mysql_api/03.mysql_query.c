#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysql/mysql.h"

int main()
{
    //MYSQL *mysql_init(MYSQL *mysql)
    //1.mysql初始化 
    MYSQL *msq = mysql_init(NULL);
    if(NULL == msq)
    {
        printf("mysql init error\n");
    }

    printf("mysql init success\n");
    
    //2.建立mysql连接
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


    //3.执行sql语句
    char * query = "insert into dept values(50, 'STUDENT', 'BEIJING')";
    int ret = mysql_query(conn, query);
    if(ret != 0)
    {
        printf("mysql query error:[%s]\n", mysql_error(msq));
    }
    //释放资源
    mysql_close(msq);
    return 0;
}
