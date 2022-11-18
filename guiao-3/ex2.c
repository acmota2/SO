#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t child = fork();
    if(child == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        _exit(1);
    } else if(child < 0) {
        perror("You're forked");
        return 1;
    } else {
        int status;
        wait(&status);
    }
}