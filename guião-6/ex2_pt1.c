#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int log = open("./log.txt", O_TRUNC | O_CREAT | O_WRONLY, 0640);
    int fifo = mkfifo("./fifo2", 0666);
    
    for(char buffer[1024] = { 0 };;) {
        
        if(fork() == 0) {
            fifo = open("./fifo2", O_RDONLY, 0666);
            for(ssize_t _read = 0; (_read = read(fifo, buffer, 1024)) > 0;) {
                write(log, buffer, _read);
            }
            close(fifo);
        }

        wait(NULL);
    }
    close(log);
}