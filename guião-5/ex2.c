#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE sizeof("Get this parent yey\n")
#define BUFFER 64

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
        char buffer[BUFFER] = { 0 };
        ssize_t reads = 0;
        for(char *buf_ptr = buffer;
            (reads = read(pipo[0], buf_ptr, 16)) > 0;
            buf_ptr += reads) {
        }
        close(pipo[0]);
        (void) write(1, buffer, SIZE);
        _exit(1);
    // sanity (c)heck
    } else if(child < 0) {
        perror("No child");
    // parent
    } else {
        close(pipo[0]);
        if(write(pipo[1], "Get this parent yey\n", SIZE) < 0) {
            perror("Parent: couldn't write");
        }
        close(pipo[1]);
    }
    wait(NULL);
}