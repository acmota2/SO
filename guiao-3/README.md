# Guião 3

Neste guião pretende-se aprender como executar outros programas através do nosso. Algum conhecimento sobre processos (ver [guiao-2](../guiao-2/)) é aconselhável.

As _system calls_ a ser usadas poderão ser encontradas no header
```c
#include <unistd.h>
```
onde as seguintes funções poderão ser encontradas:
```c
int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
```
Antes de se fazer o que quer que seja sobre este guião, há umas noções sobre como programas em C podem funcionar que deverão existir.
Se for sabido que é possível um programa receber argumentos, é certo que a forma certa de o fazer em C será:
```c
int main(int argc, char* argv[]) {
    // code
}
```
No entanto, que se pode dizer sobre `argv`? Ora, `argv[0]` é o nome do programa e `argc` é o limite de argv. Mas as funções da família `exec` não recebem nenhuma variável como argumento para saber onde este array acaba. No entanto, estas sabem-no pois este array é `NULL` _terminated_, isto é, a sua última posição é um _pointer_ para `NULL`, pelo que iterando, basta fazer algo idêntico a:
```c
// partindo do princípio que o array é o argv
while(*argv != NULL) {
    // code
}
```
Com isto depreende-se que todos os argumentos deverão ser mandados da forma `NULL` _terminated_.

Quanto à parte que diz respeito ao `exec` em si: esta família de funções efetivamente substitui a stack do _parent_ pela do programa que foi invocado com qualquer função do tipo `exec`. Formas de como fazer algo que nos dê algum controlo sobre este facto serão abordadas nos guiões seguintes.
Qualquer função do tipo `execl` terá que ter o caminho especificado para o programa que se pretende executar.
Funções que sejam do formato `execp` recebem os seus argumentos como _array_ `NULL` _terminated_ e não separados.
As funções que sejam do tipo `execv` partem do princípio que irão executar um programa existente na pasta definida como sendo _pasta dos programas_ (normalmente `/bin`) do sistema operativo.

### _Man pages_ úteis

`man 3 exec` - todas as funções aparecerão a fazer isto

### _Debugging_

Quanto a este guião apenas não há muito que se possa fazer, visto a _stack_ do processo ser completamente substituída.

* #### _bugs_ conhecidos
    * Usar uma função do tipo `execl` para um programa que exista em sistemas POSIX. Como não há um único caminho especificado, esta função irá procurar pelo programa na pasta em que o programa que invocou `exec` foi executado.