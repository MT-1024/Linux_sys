//目录操作测试 opendir() , readdir() , closedir()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
//是POSIX.1标准定义的unix类目录操作的头文件，包含了许多UNIX系统服务的函数原型，例如opendir函数、readdir函数.
#include <dirent.h>
int main(int argc, const char * argv[])
{	
	//open directory
	//DIR * opendir(const char * name);
	DIR * pDir = opendir(argv[1]);
	if(pDir == NULL)
	{
		perror("opendir error");
		return -1;
	}

	//循环读取目录项
	//struct dirent *readdir(DIR *dirp);
	struct dirent * pDent = NULL;
	while((pDent = readdir(pDir)) != NULL)
	{	
		if(strcmp(pDent->d_name, ".") == 0 || strcmp(pDent->d_name, "..") == 0)
		{
			continue;
		}
		printf("dir name ------>[%s]", pDent->d_name);

		//判断文件类型
		switch(pDent->d_type)
		{
			case DT_REG:
				printf("this regular file\n");
				break;
			case DT_DIR:
				printf("this is directory file\n");
				break;
			case DT_LNK:
				printf("link file\n");
				break;
			default:
				printf("unknow file\n");

		}
	}
	
	//close directory
	closedir(pDir);
	return 0;
}

