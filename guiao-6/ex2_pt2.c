#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        perror("too many arguments");
        return 1;
    }
    int fd = open("./fifo2", O_WRONLY, 0666);
    write(fd, argv[1], strlen(argv[1]));
    close(fd);
}