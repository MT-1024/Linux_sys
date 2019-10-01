#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> //宏定义 O_RDONLY

int main(int argc, char * argv[])
{
	int fd = open(argv[1], O_RDONLY);

	int newfd = dup(fd);

	write(newfd, "1234567", 7);
	printf("newfd = %d\n", newfd);

	return 0;
}
