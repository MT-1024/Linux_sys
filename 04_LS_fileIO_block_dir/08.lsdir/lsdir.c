#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


void rddir(char * dir, void (*func)(char *));
void isFile(char * name);

void rddir(char * dir, void (*func)(char *))
{
	//打开目录
	DIR * dp = opendir(dir);
	if(NULL == dp)
	{
		perror("opendir error");
		return;
	}

	struct dirent * dr;

	char path[256];
	//读目录项
	while((dr = readdir(dp)) != NULL)	
	{
		if(strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0)
		{   
			continue;
		} 
		//目录项本身不可访问，拼接 目录/目录项
		sprintf(path,"%s/%s", dir, dr->d_name);
		//判断文件类型，目录递归进入，文件显示名字/大小
		(*func)(path);
	}

	closedir(dp);
	return;
}


void isFile(char * name)
{
	//获取文件属性，从而判断文件类型
	struct stat st;
	int ret = 0;
	ret = stat(name, &st); 
	if(ret == -1)
	{
		perror("get stat error");
		return;
	}
	//如果是目录，则调用rddir()
	if(S_ISDIR(st.st_mode))
	{
		rddir(name, isFile);	
	}
	//如果是普通文件，则打印文件名和文件大小
	printf("%-20s\t%ld\n", name, st.st_size);


	return;
}

int main(int argc, char * argv[])
{
	//如果直接ls 
	if(argc == 1)
	{
		isFile(".");	
	}
	else
	{
		isFile(argv[1]);		
	}

	return 0;
}

