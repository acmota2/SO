# Guião 5

Neste guião pretende-se aprender a criar _pipes_, isto é, uma espécie de túnel que funcione entre processos. Estes podem ser úteis para que 2 processos comuniquem entre si, isto é, transfiram informação entre si, visto ser uma das únicas formas pela qual processos relacionados podem comunicar.
A função relativa a este guião estará no header
```c
#include <unistd.h>
```
e trata-se de
```c
int pipe(pd[2]);
```
Um pipe trata-se dum par de descritores de ficheiros especiais que funcionam como descritor de leitura e descritor de escrita. Inicializar um pipe é como se segue
```c
int pd[2];
int check = pipe(pd);
if(check < 0) {
    // error checking
}
```
O [**exercício 1**](./ex1.c) pretende mostrar como se comporta o processo de escrita num pipe. O processo que lê dum pipe irá bloquear enquanto este não for completamente escrito. Considera-se um pipe completamente escrito aquele que recebeu uma situação de _end of file_ (EOF), ou seja, aquele que foi fechado **em todos os processos que o têm aberto**. Isto depreende que o controlo de abertura e fecho de ficheiros deverá estar feito de forma a que quando um processo ler dalgum pipe, este ser fechado em todos os processos que o têm aberto, ou o processo que lê irá ficar bloqueado na situação de leitura.

O `pipe` é uma operação que pode ser generalizada em casos, sendo a descoberta desses casos um dos desafios deste guião.

### _Man pages_ úteis

`man 2 pipe`

### _Debugging_

À semelhança do que aconteceu com o caso dos `dup`, a pasta dum processo com _pid_ id voltará a ser útil para verificar _file descriptors_ abertos, ou seja, a pasta `/proc/pid/fd`.

* #### _bugs_ conhecidos
    * **Usar** `open()`: esta função nunca precisa de ser usada com `pipe`, visto a abertura e criação destes ser da total responsabilidade da função `pipe`.
    * **Ter um processo a tentar ler dum `pipe` que não desbloqueia**: a provável causa é existirem ainda processos com a ponta de escrita aberta. Verificando através dos seus _pid_ a previamente mencionada pasta pode confirmar esta suspeita.