# Guião 2

Neste guião pretende-se aprender a manipular processos através das _system calls_ nestes headers:
```c
#include <unistd.h>
#include <sys/wait.h>
```
Nestes headers poder-se-ão encontrar as seguintes funções de manipulação de processos.
```c
pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
int WIFEXITED(int status); /* macro */
int WEXITSTATUS(int status); /* macro */
```
A função `getpid()` devolve ao processo o _process id_ (pid) do mesmo. O tipo `pid_t` não é mais que um tipo que representa _pid_ em C. É, no caso de GNU C pelo menos, nada mais que:
```c
typedef int pid_t;
```
Isto é, mais uma vez, um caso em que a um tipo mais simples se faz corresponder uma estrutura maior do sistema operativo. Ou seja, cada processo é, na realidade, uma estrura maior do sistema operativo que contém, entre outras coisas, o parent, os childs e todos os _file descriptors_ abertos nele.

A função `getppid()` devolve ao atual processo o _pid_ do seu parent.

Criar processo faz-se com a função `fork()`, que ao processo pai devolve o _pid_ do filho, e ao filho irá devolver 0. Tal processo é controlado, normalmente, duma das seguintes formas:
```c
pid_t child = fork();
if(child == 0) {
    // child code
} else if(child < 0) {
    // error handling code
} else {
    // parent code
}
```
ou então:
```c
switch(fork()) {
    case 0: {
        // child code
    }
    break;
    case -1: {
        // error handling code
    }
    break;
    default: {
        // parent code
    }
}
```
A criação de processos desta forma copia o estado atual da **stack** do parent. Isto significa que quaisquer estruturas inicializadas com `malloc()` ou semelhantes formas de inicialização na **heap** do _parent_, **não** estarão no _child_.

O wait tem várias formas de ser utilizado, sendo a mais comum:
```c
wait(NULL);
```
No entanto, se alguma coisa (normalmente o _exit status_ dum filho) precisar de ser verificada, a forma correta para utilização será algo como:
```c
int status;
wait(&status);
```
Desta forma, toda a informação guardada na saída do processo anterior será guardada no `int status`. De relembrar que nem tudo neste `int status` se refere ao código de saída do processo, este corresponde apenas a 1 Byte de informação nesse `int`, pelo que a utilização das macros `WIFEXITED` e `WEXITSTATUS` é obrigatória para garantir um programa sem erros.

**Notas:** Segundo a _man page_ do `wait()` (`man 2 wait`), cada processo terá que ter um `wait()` após o seu término, independentemente deste ter garantidamente acabado ou não, pois só desta forma o sistema operativo poderá libertar todos os recursos usados por este. No entanto, esta arquitetura pode não ser a esperada na lição desta UC, pelo que tal verificação é aconselhada por parte dos alunos.

### _Man pages_ úteis

`man 2 getpid`, `man 2 getppid`, `man 2 _exit`, `man 2 wait`, `man 2 waitPID`

`WIFEXITED` e `WEXITSTATUS` têm as suas explicações nas _man pages_ do `wait()`

### _Debugging_

O `gdb`, _debugger_ favorito de toda a gente que alguma vez programou em C, tem comandos específicos para quem pretende visualizar a execução dum programa que crie processos. Nomeadamente, fornece algumas ferramentas para quem queira seguir, de forma _indolor_, a execução dos vários processos:

* `set follow-fork-mode`: esta opção permite escolher se o `gdb` deverá seguir o `parent` ou os `child`.
    ```bash
    >> set follow-fork-mode child
    >> set follow-fork-mode parent
    ```
* `set detach-on-fork mode`: esta opção permite decidir se o `gdb` deixa de acompanhar processos quando estes terminam ou não. A navegação entre processos é feita com `inferior #number`.
    ```bash
    >> set detach-on-fork mode on
    >> set detach-on-fork mode off

    >> inferior 1
    >> inferior 2
    >> ...
    ```
