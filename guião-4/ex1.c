#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open("/etc/passwd", O_RDONLY, 0640);
    int fd1 = open("./saida.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
    int fd2 = open("./erros.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);

    (void) dup2(fd, 0);
    close(fd);

    (void) dup2(fd1, 1);
    close(fd1);

    (void) dup2(fd2, 2);
    close(fd2);

    puts("terminei");
}