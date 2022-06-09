#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define NAME_SIZE 23

typedef struct {
    char name[NAME_SIZE];
    unsigned char age;
} Person;

int main(int argc, char *argv[]) {
    int fd = open("./people.bin", O_CREAT | O_RDWR, 0666);
    
    if(argc != 3) {
        static const char ARGUMENTS[] = "Invalid argument count";
        write(2, ARGUMENTS, sizeof(ARGUMENTS));
    }

    switch(argv[1][2]) {
        case 'i': {
            Person new = {
                .age = atol(argv[3])
            };
            memcpy(new.name, argv[2], strlen(argv[2]));
            lseek(fd, 0, SEEK_END);
            write(fd, &new, sizeof(Person));
            break;
        }
        case 'u': {
            int no_stop = 1;
            Person buf[6] = { 0 };
            
            Person *i = buf;
            while(read(fd, buf, sizeof(buf)) > 0 && no_stop) {
                for(i = buf; i <= &buf[5] && (no_stop = strcmp(i->name, argv[2])) == 0; ++i);
            }

            i->age = atol(argv[3]);
            lseek(fd, sizeof(buf) - (i - buf), SEEK_CUR);
            write(fd, i, sizeof(Person));
            break;
        }
        case 'o': {
            lseek(fd, sizeof(Person) * atol(argv[3]), SEEK_CUR);
            Person to_change = { 0 };
            read(fd, &to_change, sizeof(Person));

            to_change.age = atol(argv[3]);
            lseek(fd, -sizeof(Person), SEEK_CUR);
            write(fd, &to_change, sizeof(Person));
        }
    }
}