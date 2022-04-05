#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE sizeof("Get this parent\n")

int main(void) {
    int pipo[2];
    int check = pipe(pipo);
    while(check < 0) {
        perror("Cachimbo inválido.");
        check = pipe(pipo);
    }

    pid_t child = fork();
    // this is child
    if(child == 0) {
        close(pipo[1]);
        char buffer[SIZE] = { 0 };
        if(read(pipo[0], buffer, SIZE) < 0) {
            perror("Child: couldn't read");
        }
        write(1, buffer, SIZE);
        close(pipo[0]);
        _exit(1);
    // sanity (c)heck
    } else if(child < 0) {
        perror("No child");
    // parent
    } else {
        close(pipo[0]);
        if(write(pipo[1], "Get this parent\n", SIZE) < 0) {
            perror("Parent: couldn't write");
        }
        close(pipo[1]);
    }
    wait(NULL);
}