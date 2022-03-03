#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t child = fork();
    int wstatus = 1;
    pid_t waiter = wait(&wstatus);
    if(WIFEXITED(wstatus))
        printf("Parent: %ld\nCurrent: %ld\n", getppid(), child);
    else
        printf("Parent: %ld\nCurrent: %ld\nChild: %ld\n", getppid(), getpid(), child);
}