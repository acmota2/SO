#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sigalrm_handler(int signum) {
    kill(0, SIGABRT);
}

// ./multigrep palavra [ficheiro]
int main(int argc, char *argv[]) {    
    for(size_t i = 2; i < argc; ++i) {
        alarm(10);
        if(fork() == 0) {
            signal(SIGALRM, sigalrm_handler);

            execl("grep", "grep", argv[1], argv[i]);

            perror("Exec failed");
            _exit(42);
        }
    }

    for(size_t i = 0, total = 0; i < argc - 2; ++i) {
        int status;
        wait(&status);
        if(WIFEXITED(status)) {
            if(WEXITSTATUS(status) == 0) {
                kill(0, SIGINT);
                break;
            }
        }
    }
}