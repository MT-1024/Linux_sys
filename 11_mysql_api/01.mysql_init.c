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
    
    //释放资源
    mysql_close(msq);
    return 0;
}
