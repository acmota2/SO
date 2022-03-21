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

#define BUF_SIZE sizeof("Na linha 0\n")
    bool found = false;
    char buffer[10][BUF_SIZE] = { 0 };
    for(size_t i = 0; i < LINHAS; ++i) {
        int status;
        (void) wait(&status);
        if(WIFEXITED(status)) {
            int exit = WEXITSTATUS(status);
            if(exit > 12) {
                found = true;
                snprintf(buffer[exit - 12], BUF_SIZE, "Na linha %d\n", exit - 12);
            }
        }
    }
    for(size_t i = 0; i < 10; ++i) {
        if(*buffer[i] != '\0') {
            printf("%s", buffer[i]);
        }
    }
    if(!found) {
        puts("Didn't find your number.");
    }
}