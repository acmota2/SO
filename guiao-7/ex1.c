#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

unsigned seconds = 0, count = 0;

void sigint_handler(int signum) {
    char buffer[sizeof("\nSeconds passed: 4294967296\n")] = { 0 };
    sprintf(buffer, "\nSeconds passed: %d\n", seconds);
    write(1, buffer, sizeof(buffer));
    ++count;
}

void sigquit_handler(int signum) {
    char buffer[sizeof("\nCounted 4294967296\n")] = { 0 };
    sprintf(buffer, "\nCounted %d\n", count);
    write(1, buffer, sizeof(buffer));
    exit(0);
}

void sigalrm_handler(int signum) {
    ++seconds;
    alarm(1);
}

int main(void) {
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGALRM, sigalrm_handler);

    for(alarm(1);;);
}