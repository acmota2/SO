#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_P 10

int main(int argc, char *argv[]) {
    int returns[10] = { 0 };
    for(size_t i = 0; i < MAX_P; ++i) {
        pid_t child = fork();
        int status = 1;
        wait(&status);
        if(!WIFEXITED(status)) {
            printf("pid: %d\n", getpid());
            _exit(0);
        }
        else {
            returns[i] = WEXITSTATUS(status);
        }
    }
    for(size_t i = 0;
        i < MAX_P;
        printf("Exit status de %d: %d\n", i + 1, returns[i++]));
}