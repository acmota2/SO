#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 128

int my_system(char const* command) {
    char **args = malloc(SIZE * sizeof(char*));
    for(char **ptr = args; ptr < args + 8; ++ptr) {
        *ptr = malloc(SIZE);
    }

    size_t i = 0;
    for(char *end = strchr(command, ' '), *start = strchr(command, ' ');
        end != NULL;
        start = end) {
            end = strchr(command, ' ');
            memcpy(args[i++], start, end - start);
        }

    char program[128] = { 0 };
    memcpy(program, command, strchr(command, ' ') - command);

    pid_t child = fork();
    if(child == 0) {
        int exit_status = execvp(program, args);
        _exit(exit_status ? 42 : 0);
    } else if(child < 0) {
        perror("You're forked mate");
        return -1;
    } else {
        wait(NULL);
    }
    return 0;
}

#define PROGRAM "ls"

int main(int argc, char *argv[]) {
    printf("Program %s exited with code %d\n", PROGRAM, my_system(PROGRAM));
}