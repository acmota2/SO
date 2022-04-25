#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int pipo[2] = { 0 };
    (void) pipe(pipo);
    
    if(fork() == 0) {
        close(pipo[0]);
        
        dup2(pipo[1], 1);
        close(pipo[1]);


        execlp("ls", "ls", "/etc", NULL);
        _exit(1);
    }

    if(fork() == 0) {
        close(pipo[1]);
        dup2(pipo[0], 0);
        close(pipo[0]);
    
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }

    close(pipo[1]);
    close(pipo[0]);
    wait(NULL);
    wait(NULL);
}