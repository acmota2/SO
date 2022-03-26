#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINHAS 10U
#define COLUNAS 912836745UL

static int matrix[LINHAS][COLUNAS] = { 0 };

int main(int argc, char *argv[]) {
    // srand(clock());
    // // PAPI did it better, mas wtv
    // for(size_t i = 0; i < LINHAS; ++i) {
    //     for(size_t j = 0; j < COLUNAS; ++j) {
    //         matrix[i][j] = rand();
    //     }
    // }
    matrix[4][89327465] = 123;
    matrix[8][187645] = 123;
    matrix[9][13456] = 123;

    // I don't like this, but it's better
    int find_me = atoi(argv[1]);
    for(size_t i = 0; i < LINHAS; ++i) {
        pid_t child = fork();
        // each child
        if(child == 0) {
            for(size_t j = 0; j < COLUNAS; ++j) {
                if(matrix[i][j] == find_me) {
                    _exit(i + 10);
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
    bool prints[LINHAS] = { false };
    for(size_t i = 0; i < LINHAS; ++i) {
        int status;
        (void) wait(&status);
        if(WIFEXITED(status)) {
            int exit = WEXITSTATUS(status);
            if(exit > 10) {
                found = true;
                prints[exit - 10] = true;
            }
        }
    }
    for(size_t i = 0; i < LINHAS; ++i) {
        if(prints[i]) {
            printf("Encontrado na linha %zu\n", i);
        }
    }
    if(!found) {
        puts("Didn't find your number.");
    }
}