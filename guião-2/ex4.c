#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_P 10

int main(int argc, char *argv[]) {
    pid_t children[MAX_P] = { 0 };
    pid_t parents[MAX_P] = { 0 };
    pid_t print[MAX_P] = { 0 };
    for(size_t i = 0; i < MAX_P; ++i) {
        parent[i] = getpid();
        children[i] = fork();
        if(children[i]) {
            printf("Children: %ld\n", children[i]);
            _exit(i);
        }
    }

    for(size_t i = 0; i < MAX_P; ++i) {
        wait(&children[i]);
        print[i] = WIFEXITED(children[i])
            ? WEXITSTATUS(children[i])
            : continue;
    }

    for(
        size_t i = 0;
        i < MAX_P;
        printf("Children exit status: %d", print[i])
    );
}