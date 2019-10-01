//递归遍历目录实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void rtd(char * filename)
{
	DIR * pDir1 = opendir(filename);
	if(pDir1 == NULL)
	{
		perror("opendir error");
		exit(1);
	}
	struct dirent * pDent1 = NULL;

	char path[256];
	while((pDent1 = readdir(pDir1)) != NULL)
	{
		if(strcmp(pDent1->d_name, ".") == 0 || strcmp(pDent1->d_name, "..") == 0)
		{
			continue;
		}

		switch (pDent1->d_type)
		{
			case DT_REG:
				printf("%s\n", pDent1->d_name);
				break;
			case DT_DIR:
				printf("%s\n", pDent1->d_name);
				//sprintf(path, "%s/%s", pDent1->d_name, pDent1->d_name->d_name);
				//rtd(pDent1->d_name);
				break;
			default :
				printf("unknow file\n");
		}
	}
	closedir(pDir1);
}

int main(int argc, char * argv[])
{
	rtd(argv[1]);	
	return 0;
}
