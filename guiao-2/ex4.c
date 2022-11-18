#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_P 10

int main(int argc, char *argv[]) {
    for(size_t i = 0; i < MAX_P; ++i) {
        pid_t child = 0;
        // each child
        if((child = fork()) == 0) {
            printf("Child: %d\nParent: %d\n", getpid(), getppid());
            _exit(i);

        // terrible error handling
        } else if(child < 0) {
            perror("You're forked");
            return 1;
        }
    }

    for(size_t i = 0; i < MAX_P; ++i) {
        int status;
        pid_t child = wait(&status);
        
        if(WIFEXITED(status)) {
            int exit = WEXITSTATUS(status);
            printf("Exit code de %d: %u\n", child, exit);
        }
    }
}