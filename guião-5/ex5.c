#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void the_piper_at_the_gates_of_read(int pipo[2], char *command, char *argv[]) {
    if(fork() == 0) {
        close(pipo[1]);
        dup2(0, pipo[0]);
        close(pipo[0]);

        execv(command, argv);
        _exit(1);
    }
}

void the_piper_at_the_gates_of_write(int pipo[2], char *command, char *argv[]) {
    if(fork() == 0) {
        close(pipo[0]);
        dup2(1, pipo[1]);
        close(pipo[1]);

        execv(command, argv);
        _exit(1);
    }
}

int main(void) {
    int pipo[2] = { 0 };
    (void) pipe(pipo);

    char *grep_argv[] = {"-v", "^#", "/etc/passwd", NULL};
    the_piper_at_the_gates_of_write(
        pipo,
        "grep",
        grep_argv
    );

    char *cut_argv[] = {"-f7", "-d:", NULL};
    the_piper_at_the_gates_of_read(
        pipo,
        "cut",
        cut_argv
    );

    char *uniq_argv[] = {NULL};
    the_piper_at_the_gates_of_read(
        pipo,
        "uniq",
        uniq_argv
    );

    char *wc_argv[] = {"-l", NULL};
    the_piper_at_the_gates_of_read(
        pipo,
        "wc",
        wc_argv
    );
}