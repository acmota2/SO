#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t child = fork();
    if(getpid() != child)
        printf("Parent: %ld\nCurrent: %ld\n", getppid(), child);
    else
        printf("Parent: %ld\nCurrent: %ld\nChild: %ld\n", getppid(), getpid(), child);
}