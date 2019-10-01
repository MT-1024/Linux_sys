#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h> //define off_t , ssize_t
#include<unistd.h> //Linux program
#include<fcntl.h>

int main(int argc, char * argv[])
{
	int fd = open("./test.log" , O_RDWR | O_CREAT , 0777);
	if(fd < 0)
	{
		perror("open test.log error");
		exit(1);
	}
	write(fd, "hello world", sizeof("hello world"));

	lseek(fd, 0, SEEK_SET);

	char buff[1024];
	memset(buff, 0, sizeof(buff));

	int n = read(fd, buff, sizeof(buff));
	printf("n==[%d],buff==[%s]\n", n, buff);
	return 0;
}

