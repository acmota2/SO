#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINHAS 10U
#define COLUNAS 912836745UL


int main(int argc, char *argv[]) {    
    // srand(clock());
    // // PAPI did it better, mas wtv
    // for(size_t i = 0; i < LINHAS; ++i) {
    //     for(size_t j = 0; j < COLUNAS; ++j) {
    //         matrix[i][j] = rand();
    //     }
    // }
    static int matrix[LINHAS][COLUNAS] = { 
        [4] = {
            [89327465] = 123
        },
        [8] = {
            [187645] = 123
        },
        [9] = {
            [13456] = 123
        },
    };

    // I don't like this, but it's better
    int find_me = atoi(argv[1]);
    for(size_t i = 0; i < LINHAS; ++i) {
        pid_t child = fork();
        // each child
        if(child == 0) {
            for(size_t j = 0; j < COLUNAS; ++j) {
                if(matrix[i][j] == find_me) {
                    printf("Found number on position %zu\n", j);
                    _exit(i + 12);
                }
            }
            _exit(i);
        // error handling
        } else if(child < 0) {
            perror("You're forked");
            return 1;
        }
    }

    bool found = false;
    for(size_t i = 0; i < LINHAS; ++i) {
        int status;
        (void) wait(&status);
        if(WIFEXITED(status)) {
            int exit = WEXITSTATUS(status);
            if(exit > 12) {
                found = true;
                printf("Na linha %d\n", exit - 12);
            }
        }
    }
    if(!found)
        puts("Didn't find your number.");
}