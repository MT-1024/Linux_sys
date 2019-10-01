#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char  * argv[])
{
	//int stat(const char * pathname, struct stat * buf);
	struct stat st;
	stat(argv[1], &st);
	printf("size:[%ld], uid:[%d], gid:[%d]\n", st.st_size, st.st_uid, st.st_gid);

	return 0;
}
