#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define COM 4

int main(void) {
    static char *commands_grep[] = {"grep", "-v", "^#", "/etc/passwd", NULL};
    static char *commands_cut[] = {"cut", "-f7", "-d:", NULL};
    static char *commands_uniq[] = {"uniq", NULL};
    static char *commands_wc[] = {"wc", "-l", NULL};

    static char **commands[] = {
        commands_grep,
        commands_cut,
        commands_uniq,
        commands_wc
    };

    int pipo[COM - 1][2] = { 0 };

    for(size_t i = 0; i < COM; ++i) {
        if(i == 0) {
            pipe(pipo[0]);
            if(fork() == 0) {

                dup2(pipo[0][1], 1);
                close(pipo[0][0]);
                close(pipo[0][1]);

                execvp(commands[0][0], commands[0]);

                perror("Exec failed");
                _exit(1);
            }
            close(pipo[0][1]);

        } else if(i < COM - 1) {
            pipe(pipo[i]);
            if(fork() == 0) {

                dup2(pipo[i - 1][0], 0);
                // o de escrita anterior está fechado
                close(pipo[i - 1][0]);

                dup2(pipo[i][1], 1);
                close(pipo[i][0]);
                close(pipo[i][1]);


                execvp(commands[i][0], commands[i]);

                perror("Exec failed");
                _exit(1);
            }
            close(pipo[i - 1][0]);
            close(pipo[i][1]);


        } else {
            if(fork() == 0) {

                dup2(pipo[i - 1][0], 0);
                close(pipo[i - 1][1]);
                close(pipo[i - 1][0]);

                execvp(commands[i][0], commands[i]);

                perror("Exec failed");
                _exit(1);
            }
            close(pipo[i - 1][0]);
        }
    }
    for(size_t i = 0; i < COM; ++i) {
        wait(NULL);
    }
}