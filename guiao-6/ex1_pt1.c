#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    if(mkfifo("fifo", 0666) < 0) {
        perror("Couldn't create fifo");
        return 1;
    }
}