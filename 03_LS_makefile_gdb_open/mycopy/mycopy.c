#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

#define N 8192 
int main(int argc, char * argv[])
{
	
	int fd1 = open(argv[1], O_RDONLY);
	if(-1 == fd1)
	{
		perror("open argv[1] error");
		exit(1);
	}
	int fd2 = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(-1 == fd2)
	{
		perror("open argv[2] error");
		exit(1);
	}
	char buff[N];
	int n = 0;

	while( n = read(fd1,buff, N))
	{
		
		if(-1 == fd2)
		{
			perror("open argv[2] error");
			exit(1);
		}
		write(fd2, buff, n);
	}
	
	close(fd2);
	close(fd1);
	
	return 0;
}

