//link()用来创建一个新的dentry(文件名+inode)
//unlinl()用来删除原来的老的dentry
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char * argv[])
{
	link(argv[1], argv[2]);
	unlink(argv[1]);	
	return 0;
}
