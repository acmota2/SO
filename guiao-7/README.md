# Guião 7

Neste guião pretende-se aprender a trabalhar com sinais e a gerir processos através destes. Para tal irão ser usados os headers:
```c
#include <signal.h>
#include <sys/types.h>
```
que contêm as funções
```c
sighandler_t signal(int signum, sighandler_t handler);
int kill(pid_t pid, int sig);
unsigned int alarm(unsigned int seconds);
int pause(void);
```
O tipo `sighandler_t` é um _function pointer_ cuja definição é:
```c
typedef void(*sighandler_t)(int);
```
**Apenas a título de curiosidade**: assume-se que este existe para tornar a função `signal()` mais fácil de ler, senão esta seria:
```c
void (*signal(int signum, void(*sighandler)(int)))(int);
```
A execução dum sinal efetivamente interrompe a execução atual dum qualquer processo que o receba. Isto significa que operações de _IO_ podem ser interrompidas por um sinal, pelo que se apela ao bom senso de quem programa a forma como se utilizam.

A função `signal()` associa a um sinal, especificado no primeiro argumento com uma _flag_, a função que o processo em questão deverá executar quando recebe esse mesmo sinal. Este sinal pode ser enviado dum qualquer processo através da função `kill()`.
Observe-se o seguinte exemplo, meramente ilustrativo, que pretende acabar qualquer processo quando recebe o sinal `SIGQUIT`:
```c
int sigquit_handler(int signum) {
    (void) signum;
    kill(getpid(), SIGINT);
}

int main(void) {
    (void) signal(SIGQUIT, sigint_handler);
    // rest of the code
}
```
A função `alarm()` é nada mais que um temporizador que conta, em segundos, quanto tempo até um processo enviar um `SIGALRM`. Isto pode ser útil para executar alguma ação, ou, por exemplo, para envio doutro sinal.
Por fim, a função `pause()` interrompe um processo até que este receba um qualquer sinal que o termine ou que tenha um `sighandler` associado.

### _Man pages_ úteis

`man 2 signal`, `man 2 alarm`, `man 2 pause`

### _Debugging_

A única forma de saber que sinais resultaram num processo é acompanhar a execução deste no `gdb`, mas para isso é preciso que outro processo os mande. Para isso é possível usar-se o comando `kill`, que, à semelhança da função em `signal.h` com o mesmo nome, envia sinais a um processo, desta vez pelo seu _pid_:
```bash
# haja um processo com o pid 1234
>> kill -2 1234
# este comando irá enviar SIGINT ao processo 1234
```
Desta forma é possível, sem criar um programa propositadamente para o efeito, enviar um sinal a um processo, conhecendo-se o seu _pid_. Uma forma simples de se conhecer um _pid_ dum programa (neste caso do parent) conhecendo o seu nome é `ps aux | grep "nome"`.

* #### _bugs_ conhecidos
    * `kill(0, um_sinal)`**:** isto vai efetivamente enviar um sinal a todos os processos naquele grupo, **incluindo o próprio**. 
    Se esse sinal for um `SIGINT`, por exemplo, a predefenição deste sinal é interromper qualquer processo que o receba, pelo que todos os processos, incluindo o próprio, irão ser interrompidos.
    * `SIGINT` **vs** `SIGTERM`**:** enquanto que a predefinição de qualquer um destes é interromper o processo imediatamente, quando se prime `CTRL+C` no terminal, o término imediato dum programa é o comportamento esperado. Isto quer dizer que o comportamento deste sinal só em raras ocasiões deverá ser alterado.
    O `SIGTERM`, por outro lado, serve para terminar _suavemente_ um processo, ou seja, espera-se que aquando da chamada deste, um processo acabe todo o trabalho que ainda tem pendente e eventualmente termine, demore isso 2min ou 2h.
