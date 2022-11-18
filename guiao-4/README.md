# Guião 4

Neste guião pretende-se aprender como duplicar descritores de ficheiros, ou seja, como redirecionar operações dum ficheiro para outro e _guardar_ descritores de ficheiros que possam vir a ser alterados.

Para tal, o heeader a ser utilizado será
```c
#include <unistd.h>
```
e as funções serão
```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
Apenas em raros casos se utiliza a função `dup`, sendo preferida a utilização da função `dup2` na maioria dos casos.
Uma utilização muito standard é a seguinte:
```c
// assuma-se a existência dum int fd1 e um int fd2
int new_fd = dup2(fd1, fd2);
if(new_fd < 0) {
    // error handling
}
close(fd1);
```
Esta utilização faz com que `fd2` se refira ao ficheiro a que `fd1` se referia, tendo sido este último redirecionado para `fd2`. Após redirecionar-se, fecha-se o antigo descritor. Caso os decritores se refiram aos standard (in, out, error), estes não deverão ser fechados.

### _Man pages_ úteis

`man 2 dup`, `man 2 dup2`

### _Debugging_

As pastas correspondentes aos processos existem no sistema operativo no caminho **`/proc`**. Sabendo-se o _pid_ do processo, toda a informação relativa a este, incluindo _file descriptors_ estará dentro da pasta `/proc/pid`, estando os _file descriptors_ abertos neste na pasta `/proc/pid/fd`. Aqui poder-se-ão verificar os destinos de todos os `dups` feitos e a forma como estes _realmente_ funcionam. Esta técnica irá voltar a ser útil.

* #### _bugs_ conhecidos
    * Não fechar um ficheiro no fim de fazer um `dup`.
    * Fechar qualquer um dos ficheiros _standard_, ou seja, os `standard input | output | error`.

**Notas:** como saber o _pid_ dum processo? O [guião 1](../enunciados_guioes/guiao-01.pdf) referia uma função chamada `getpid()` que pode ser usada para este efeito no presente processo:
```c
// assuma-se my_stdout como o standard output correto
pid_t my_pid = getpid();
char buffer[11] = { 0 };
int size = snprintf(buffer, sizeof(buffer), "%d\n", my_pid);
write(my_stdout, buffer, size);
```
No caso do _pid_ provir dum _fork_ é semelhante, mas não há necessidade de fazer `getpid()` pois a função `fork()` retorna o _pid_ do _child_ ao _parent_.