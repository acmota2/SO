#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    unsigned char buffer[4096] = { 0 };
    for(ssize_t i = read(0, buffer, 4096); i > 0; i = read(0, buffer, 4096)) {
        write(1, buffer, i);
    }
    return 0;
}
