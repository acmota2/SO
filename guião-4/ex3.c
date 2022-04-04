#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int terminal = dup(1);

    int fd = open("/etc/passwd", O_RDONLY, 0640);
    int fd1 = open("./saida.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
    int fd2 = open("./erros.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);

    (void) dup2(fd, 0);
    close(fd);

    (void) dup2(fd1, 1);
    close(fd1);

    (void) dup2(fd2, 2);
    close(fd2);

    int worked = execl("/bin/wc", "wc", NULL);
    if(worked < 0) {
        perror("Didn't work.");
    }

    write(terminal, "terminei\n", sizeof("terminei\n"));
}