#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    unsigned char buf[4096];

    // para efeitos de teste:
    // int buf_s = atoi(argv[3]);
    // char *buffer = malloc(buf_s);

    if(!argv[1] || !argv[2]) {
        return -1;
    }

    int fd1 = open(argv[1], O_RDONLY, 0660);
    if(fd1 < 0) {
        perror("Invalid file.");
        return -1;
    }

    int fd2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0660);
    if(fd2 < 0) {
        perror("Invalid file.");
        return -1;
    }

    for(ssize_t i = read(fd1, buffer, buf_s); i > 0; i = read(fd1, buf, 4096)) {
        write(fd2, buf, i);
    }
    return 0;
}