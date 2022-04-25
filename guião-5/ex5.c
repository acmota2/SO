void the_piper_at_the_gates_of_read(int pipo[2], char *command, char *argv[]) {
    if(fork() == 0) {
        close(pipe[1]);
        dup2(0, pipo[0]);
        close(pipo[0]);

        execv(command, argv);
        _exit(1);
    }
}

void the_piper_at_the_gates_of_write(int pipo[2], char *command, char *argv[]) {
    if(fork() == 0) {
        close(pipe[0]);
        dup2(1, pipo[1]);
        close(pipo[1]);

        execv(command, argv);
        _exit(1);
    }
}

int main(void) {

}