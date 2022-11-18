#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *const args[] = {
        "ls -l", NULL
    };
    execvp(args[0], args);
}