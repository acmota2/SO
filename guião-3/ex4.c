#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

int my_system(char const* command) {
    pid_t child = fork();
    if(child == 0) {
        int exit_status = execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(0 - (exit_status < 0));
    } else if(child < 0) {
        perror("You're forked mate");
        return -1;
    } else {
        wait(NULL);
        return 0;
    }
}

int main(int argc, char *argv[]) {

}