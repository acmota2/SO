#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int fifo_fd = open("./fifo", O_WRONLY);
    if(fifo_fd < 0) {
        perror("Couldn't open fifo");
        return 1;
    }
    char buffer[1024] = { 0 };
    
    ssize_t _read = 0;
    while((_read = read(0, buffer, 1024)) > 0) {
        write(fifo_fd, buffer, _read);
    }

    close(fifo_fd);
}