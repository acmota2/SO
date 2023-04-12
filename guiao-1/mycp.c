#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc < 3) {
        perror("Invalid file(s).");
        return -1;
    }

    int fd1 = open(argv[1], O_RDONLY, 0660);
    if(fd1 < 0) {
        perror("Invalid file.");
        close(fd1);
        return -1;
    }

    int fd2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if(fd2 < 0) {
        perror("Invalid file.");
        close(fd2);
        return -1;
    }

    unsigned char buffer[4096] = { 0 };

    size_t buf_s = 4096;
    if(argc == 4) {
        char *save = NULL;
        buf_s = strtol(argv[3], &save, 10);
        buf_s = 4096 < buf_s ? 4096 : buf_s;
        if(!save) {
            static const char ERROR[] = "This is not the size you wanted.";
            write(1, ERROR, sizeof(ERROR));
            return -1;
        }
    }

    for(ssize_t i = read(fd1, buffer, buf_s); i > 0; i = read(fd1, buffer, buf_s)) {
        write(fd2, buffer, i);
    }
    return 0;
}
