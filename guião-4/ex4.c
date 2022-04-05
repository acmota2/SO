#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    size_t i = 1;
    if(argc == 1) {
        fputs("This program needs arguments to run!\n", stderr);
        return 1;
    }
    for(; *argv[i] == '-'; i++) { // porque entrada e saída
        int fdr = 0, fdw = 1;

        switch(argv[i][1]) {
            case 'i':
                fdr = open(argv[++i], O_CREAT | O_RDONLY | O_TRUNC, 0640);
                (void) dup2(fdr, 0);
                close(fdr);
                break;
            case 'o':
                fdw = open(argv[++i], O_CREAT | O_WRONLY | O_TRUNC, 0640);
                (void) dup2(fdw, 1);
                close(fdw);
                break;
            default:
                fputs("not a valid argument!", stderr);
                return 1;
        }
    }

    (void) execv(argv[i + 1], &argv[i + 2]);
}