#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main()
{
	
	int fd = open("./bible.txt.bak", O_RDONLY , 0644);
	printf("fd = %d , errno=%s\n", fd , strerror(errno));
	close(fd);
	return 0;
}

