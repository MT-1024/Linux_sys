//模拟MySQL命令行客户端
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
    MYSQL *conn = mysql_real_connect(msq, "localhost", "wjf", "321284", "scott", 0, NULL, 0);
    if(conn == NULL)
    {
        printf("mysql connect error:[%s]\n", mysql_error(msq));
    }
    printf("mysql connect success\n");

    //获取当前连接的字符集
    printf("before set character : %s\n", mysql_character_set_name(conn));

    //设置默认使用的编码集
    mysql_set_character_set(conn, "utf8");
    printf("after character : %s\n", mysql_character_set_name(conn));

    //循环等待用户输入
    char buf[1024];
    int ret;
    int colnum;
    while(1)
    {
        //打印提示符，write()是无缓冲函数，会立即将字符串打印到屏幕
        //而printf()是行缓冲，需要等到缓冲区或者遇到回车才会将字符串打印到屏幕
        write(STDOUT_FILENO, "mysql> ", strlen("mysql>"));

        //接收用户输入
        memset(buf, 0 , sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));

        //去掉buf末尾回车
        buf[strlen(buf) - 1] = '\0';

        //去掉buf末尾的分号
        char * p = strchr(buf, ';');
        if(p != NULL)
        {
            *p = '\0';
        }

        //过滤掉buf前面的空格
        int pos; 
        int len = strlen(buf);
        for(pos = 0; pos < strlen(buf); pos++)
        {
           if(buf[pos] == ' ') 
           {
               continue;
           }
           else
           {
               break;
           }
        }
        memmove(buf, buf + pos, len + 1 - pos);
        printf("buf==[%s]\n", buf);

        //判断用户输入的是否为exit或者quit, 如果是则退出
        if(strncasecmp(buf, "exit", 4) == 0 || strncasecmp(buf, "quit", 4) == 0)
        {
            mysql_close(conn);
            exit(0);
        }

        //执行SQL语句
        ret = mysql_query(conn, buf);
        if(ret != 0)
        {
            printf("%s\n", mysql_error(conn));
            continue; 
        }
        //如果用户输入的不是select查询，则打印影响的行数
        if(strncasecmp(buf, "select", 6) != 0)
        {
            printf("Query ok, %lld row affected\n", mysql_affected_rows(conn)); 
            continue;
        }

        //下面是selec查询的情况
        //获取结果集
        MYSQL_RES * result_set = mysql_store_result(conn);
        if(NULL == result_set)
        {
            printf("mysql_store_result_set error, %s\n", mysql_error(conn));
            continue;
        }
        //获取表的列数
        colnum = mysql_num_fields(result_set);

        //获取表头信息
        MYSQL_FIELD * fields = mysql_fetch_fields(result_set);
        if(NULL == fields)
        {
            printf("mysql_fetch_fields error, %s\n", mysql_error(conn));
            //释放结果集
            mysql_free_result(result_set);
            continue;
        }
        //打印表头
        printf("\n---------------------------------\n");
        for(int i = 0; i < colnum; i++)
        {
            printf("%s  ", fields[i].name);
        }
        printf("\n---------------------------------\n");

        //打印每行记录
        MYSQL_ROW row = NULL;
        while(row = mysql_fetch_row(result_set))
        {
            for(int i = 0; i < colnum; ++i)
            {
                printf("%s  ", row[i]);
            }
            printf("\n");
        }




    }

    //释放资源
    mysql_close(msq);
    return 0;
}
