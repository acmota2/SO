#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_P 10

int main(int argc, char *argv[]) {
    pid_t children[MAX_P] = { 0 };
    int exit[MAX_P] = { 0 };
    for(size_t i = 0; i < MAX_P; ++i) {
        pid_t child = 0;
        // each child
        if((child = fork()) == 0) {
            printf("Child: %d\nParent: %d\n", getpid(), getppid());
            _exit(i);
        
        // parent - the one
        } else if(child > 0) {
            int status;
            wait(&status);
            children[i] = child;
            if(WIFEXITED(status)) {
                exit[i] = WEXITSTATUS(status);
            }

        // terrible error handling
        } else {
            perror("You're forked");
            return 1;
        }
    }

    for(size_t i = 0; i < MAX_P; ++i) {
        printf("Exit code de %d: %u\n", children[i], exit[i]);
    }
}