#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t readln_bad(int fd, char *line, size_t size) {
    ssize_t _read = 0;

    for(char *buf_iter = line;
        buf_iter != '\n' && (_read += read(fd, buf_iter, 1));
        ++buf_iter);
    
    return _read;
}

// tentar o buffer global
#define BUF_SIZE 4096
ssize_t readln(int fd, char *line, ssize_t size) {
    ssize_t _read = 0;
    char buf[BUF_SIZE];

    size_t i = 0;
    while(_read += read(fd, buf, BUF_SIZE)) {
        for(size_t j = 0; buf[j] != '\n' && size-- && j < BUF_SIZE; ++i, ++j) {
            line[j] = buf[j];
        }
    }

    if(i - size)
        lseek(fd, i - size, SEEK_CUR);

    return _read;
}
#undef BUF_SIZE

void write_number(size_t line) {
    char buf[20];
    
}

int main(int argc, char *argv[]) {

}