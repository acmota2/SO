#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int fifo_fd = open("./fifo", O_RDONLY);
    if(fifo_fd < 0) {
        perror("Couldn't open fifo");
        return 1;
    }
    char buffer[1024] = { 0 };
    
    ssize_t _read = 0;
    while((_read = read(fifo_fd, buffer, 1024)) > 0) {
        write(1, buffer, _read);
    }

    close(fifo_fd);
}