#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t readln(int fd, char *line, size_t size) {
    char buf[4096];
    ssize_t _read = 0;
    char *buf_iter = buf;
    
    while(_read = read(fd, buf_iter, 1)) {
        if(*buf_iter = '\n')
            break;
        ++buf_iter;
    }
}