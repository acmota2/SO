#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
    int pipo[2] = { 0 };
    (void) pipe(pipo); 
    pit_t child = fork();
    // child
    if(child == 0) {
        int fdw = dup2(pipo[0], 0);
        close(pipo[0]);
    // sanity (c)heck
    } else if(child < 0) {
        perror("Child: couldn't create");
    // parent
    } else {
        
    }
}