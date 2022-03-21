#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t child = fork();
    if(pid != 0) {
        printf("Processo: %ld\nParent: %ld", getpid(), getppid());
    }
}