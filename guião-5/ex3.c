#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define STRING \
    "As armas e os baroes assinalados\n \
    Que da Ocidental praia Lusitana,\n \
    Por mares nunca de antes navegados\n \
    Passaram ainda alem da Taprobana,\n \
    Em perigos e guerras esforcados,\n \
    Mais do que prometia a força humana,\n \
    E entre gente remota edificaram\n \
    Novo reino, que tanto sublimaram;\n"
#define STRSIZE sizeof(STRING)
#define BUFFER_S 1024

int main(void) {
    int pipo[2] = { 0 };
    (void) pipe(pipo); 
    pid_t child = fork();
    // child
    if(child == 0) {
        close(pipo[1]);
        dup2(pipo[0], 0);
        close(pipo[0]);

        execlp("wc", "wc", NULL);
        _exit(1);
    // sanity (c)heck
    } else if(child < 0) {
        perror("Child: couldn't create");
    }
    // parent
    close(pipo[0]);
    char buffer[BUFFER_S] = { 0 };
    
    
    for(
        ssize_t _read = 0;
        (_read = read(0, buffer, 1024)) > 0;
        write(pipo[1], buffer, _read)
    );
    close(pipo[1]);
    wait(NULL);
}