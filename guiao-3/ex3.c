#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    for(size_t i = 1; i <= argc; ++i) {
        pid_t child = fork();
        if(child == 0) {
            execl(argv[i], argv[i], NULL, NULL);
            _exit(i);
        } else if(child < 0) {
            perror("You're forked");
            return 1;
        }
    }
    // waiter
    for(size_t i = 1; i <= argc; ++i) {
        int status;
        pid_t child = wait(&status);
        if(WIFEXITED(status)) {
            printf("Process %d exited with code %u\n", child, WEXITSTATUS(status));
        }
    }
}