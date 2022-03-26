#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd = open("/etc/passwd", O_RDONLY, 0640);
    int fd1 = open("./saida.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);
    int fd2 = open("./erros.txt", O_RDWR | O_CREAT | O_TRUNC, 0640);

    (void) dup2(fd, 0);
    close(fd);

    (void) dup2(fd1, 1);
    close(fd1);

    (void) dup2(fd2, 2);
    close(fd2);

    pid_t child = fork();
    // child stuff
    if(child == 0) {
        char buffer[1000] = { 0 };
        ssize_t r_bytes = read(0, buffer, 1000);
        if(r_bytes < 0) {
            perror("This didn't go well");
            _exit(1);
        }
            
        write(1, buffer, r_bytes);
        _exit(0);
    } else if(child < 0) {
        perror("You're forked");
        return 1;
    // parent
    } else {
        int status;
        child = wait(&status);
        if(WIFEXITED(status) && WEXITSTATUS(status) != 1) {
            puts("Impressos os descriptors do processo filho");
        } else {
            fputs("Fodeu geral\n", stderr);
        }
    }

    puts("terminei");
}