# Guião 1

Neste guião pretende-se aprender a manipular ficheiros através das _system calls_ para operações com ficheiros. Estas podem ser encontradas nos headers:
```c
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
```
Estes headers disponibilizarão as funções
```c
// abertura e fecho de ficheiros
int open(const char *path, int oflag);
int close(int fildes);

// modificação de ficheiros
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);

// modificação da "ponta" de leitura de ficheiros
off_t lseek(int fd, off_t offset, int whence);
```
assim como flags que possam ser úteis para modos de abertura.
A modificação de ficheiros através de _system calls_ é muito semelhante àquela das funções da `stdio` de C, com a exceção do tipo que representa um ficheiro. Aqui irão chamar-se _file descriptors_ e terão o tipo `int`.
Cada _file descriptor_ terá associada uma estrutura do sistema operativo.Esta será responsável por toda a informação relativa àquele ficheiro, ou seja, permissões, abertura, ponta de escrita e quem o abriu.
**Todo o ficheiro deverá ser fechado com `fclose`**.

As funções relativas a leitura e escrita (`read` e `write`) retornarão quantos bytes leram dum ficheiro. Este `return` seria do tipo `size_t`, como tudo quanto é tamanho em C, mas como retornam um valor negativo em casos de insucesso (que devem ser verificados, consultar `man 2 read|write`), retornam um _signed `size_t`_, ou seja, um `ssize_t`.

## _Man pages_ úteis

`man 2 open`, `man 2 close`, `man 2 read`, `man 2 write`, `man 2 lseek`