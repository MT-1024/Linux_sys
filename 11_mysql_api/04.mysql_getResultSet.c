//获取结果集
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
    MYSQL *conn = mysql_real_connect(msq, "localhost", "wjf", "321284", "scott", 3306, NULL, 0);
    if(conn == NULL)
    {
        printf("mysql connect error:[%s]\n", mysql_error(msq));
    }
    printf("mysql connect success\n");
    if(conn == msq)
    {
        printf("conn and msq is same\n");
    }


    //3.执行sql语句, 获取结果集
    char * query = "select * from dept"; 
    int ret = mysql_query(conn, query);
    if(ret != 0)
    {
        printf("mysql query error:[%s]\n", mysql_error(msq));
    }
    
    //4.获取结果集
    MYSQL_RES * result_set = mysql_store_result(conn);
    if( NULL == result_set )
    {
        printf("mysql GET_RESULT_SET ERROR:[%s]\n", mysql_error(conn));
    }
    

    
    int colnum = mysql_num_fields(result_set);
    
    //获取表的字段信息
    printf("\n--------------------------------------------------\n");
    MYSQL_FIELD * field = mysql_fetch_fields(result_set);
    for(int i = 0; i < colnum; i++)
    {
        printf("%s  ", field[i].name);
    }
    printf("\n--------------------------------------------------\n");

    //5.循环获取每一条记录
    MYSQL_ROW row= NULL;
    while(row = mysql_fetch_row(result_set))
    {
        //printf("%s | %s | %s\n", row[0], row[1], row[2]);
        for(int i = 0; i < colnum; i++)
        {
            printf("%s  ", row[i]);
        }
        printf("\n");

    } 
    //6.释放结果集
    mysql_free_result(result_set);
    //释放资源
    mysql_close(msq);
    return 0;
}
