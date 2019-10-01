#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/types.h> ,<unistd.h>中已经包含了<sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char  * argv[])
{
	//int stat(const char * pathname, struct stat * buf);
	struct stat st;
	stat(argv[1], &st);
	//1.判断文件类型
	if((st.st_mode & S_IFMT) == S_IFREG)
	{
		printf("this is regular file\n");
	}

	if(S_ISREG(st.st_mode))
	{
		printf("this is regular file\n");
	}

	//2.判断文件权限
	if(st.st_mode & S_IROTH)
	{
		printf("---R----\n");
	}
	return 0;
}

