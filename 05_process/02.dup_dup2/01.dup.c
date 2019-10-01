#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{

    int fd = open(argv[1], O_RDONLY);

    int newfd;

    dup2(fd, newfd);

    printf("oldfd=%d\n", fd);

    printf("newfd=%d\n", newfd);

    //close(fd);
    //close(newfd);
    return 0;
}
