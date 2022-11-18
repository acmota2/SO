# Guião 6

Neste guião é suposto aprender-se a usar _FIFO_. A _system call_ referente a este guião encontrar-se-à nos seguintes headers
```c
#include <sys/types.h>
#include <sys/stat.h>
```
e a função é:
```c
int mkfifo(const char *pathname, mode_t mode);
```
Ao contrário do que acontecia com _pipe_, um _FIFO_ irá bloquear o(s) processo(s) que escreve(m) para ele até que haja algum processo a ler do _FIFO_.

Criar um _FIFO_ num caminho específico irá criar um ficheiro especial nessa pasta, cujas permissões serão atribuídas no segundo argumento da função `mkfifo()`. Um exemplo de utilização segue-se:
```c
static const char pathname[] = "."; // pasta atual

int fifo_fd = mkfifo(pathname, 0666);
if(fifo_fd < 0) {
    // error handling code
}
```
A função `mkfifo()` retorna assim um _file descriptor_ para o _FIFO_ criado, e, como o _FIFO_ existe no sistema de ficheiros, este poderá ser usado e visto por qualquer programa, mesmo que não pertenca à árvore de processos que o criou.
Por estas razões indicadas acima, a utilização dum _FIFO_ por qualquer outro programa é semelhante à utilização dum ficheiro normal, como se segue:
```c
// num programa a correr na mesma pasta que o que criou o FIFO
static const char pathname[] = ".";

int fifo_fd = open(pathname, O_WRONLY);
if(fifo_fd < 0) {
    // error handling code
}

static const char message[] = "Hello, world!\n";
write(fifo_fd, message, sizeof(message));
```
A operação de escrita foi agora bloqueada até que haja outro processo que leia deste _FIFO_, algo que é feito de forma muito idêntica à escrita (não esquecer a alteração do modo de abertura do _FIFO_).

Uma função que poderá ser útil, caso se queira eliminar o _FIFO_ no fim da execução é:
```c
int unlink(const char *pathname);
```
Esta função elimina qualquer ficheiro.

### _Man pages_ úteis

`man 3 mkfifo`, `man 2 unlink`

#### _Debugging_

Tratando-se de mais uma operação sobre ficheiros, aconselha-se na mesma a ir à pasta `/proc/pid/fd` para verificar quantos ficheiros estão abertos. Esta será, no entanto, com a verificação contrária, ou seja, ver quantos têm o _FIFO_ aberto no modo de escrita, pois esta bloqueia enquanto nenhum ler.

* #### _bugs_ conhecidos
    * **Criar um _FIFO_ e não o abrir:** criar um _FIFO_ não implica que este foi aberto. Após a sua criação este deverá ser aberto na mesma, caso usá-lo seja pretendido.
    * `O_WRONLY` **num processo que deveria escrever:** mudar para `O_RDONLY` ou `O_RDWR` consoante o pretendido.
    * `O_RDONLY | O_TRUNC`**:** esta combinação pode ser perigosa, pois o processo que lê irá ler um ficheiro truncado, ou seja, para todos os efeitos, um ficheiro vazio, pelo que a informação escrita foi perdida.

Criar _FIFO_ pode ser feito através do comando `fifo` também. Para mais informações consultar `man fifo`.