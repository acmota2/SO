#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int buf_s = atoi(argv[3]);
    char *buffer = malloc(buf_s);

    int fd1 = open(argv[1], O_CREAT | O_RDWR, 0660);
    if(fd1 < 0) {
        perror("Invalid file.");
        return -1;
    }

    int fd2 = open(argv[2], O_CREAT | O_RDWR, 0660);
    if(fd2 < 0) {
        perror("Invalid file.");
        return -1;
    }

    while(read(fd1, buffer, buf_s)) {
        write(fd2, buffer, buf_s);
    }
    return 0;
}