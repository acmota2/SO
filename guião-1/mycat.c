#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    unsigned char buf[4096];
    for(ssize_t i = read(0, buffer, buf_s); i > 0; i = read(0, buf, 4096)) {
        write(1, buf, i);
    }
    return 0;
}