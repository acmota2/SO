#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Processo: %ld\nParent: %ld", getpid(), getppid());
}