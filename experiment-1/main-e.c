#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_SEMAFOROS 1
#define CHAVE_SEMAFORO 1234

int main() {
    int id_semaforo, semaforo;
    struct sembuf operacao;
    key_t chave = CHAVE_SEMAFORO;

    if ((id_semaforo = semget(chave, NUM_SEMAFOROS, IPC_CREAT | 0666)) == -1) {
        perror("Erro ao criar semaforo");
        exit(EXIT_FAILURE);
    }

    if (semctl(id_semaforo, 0, SETVAL, 1) == -1) {
        perror("Erro ao inicializar semaforo");
        exit(EXIT_FAILURE);
    }

    operacao.sem_num = 0;
    operacao.sem_op = -1;
    operacao.sem_flg = 0;

    semaforo = semop(id_semaforo, &operacao, 1);
    if (semaforo == -1) {
        perror("Erro ao decrementar semaforo");
        exit(EXIT_FAILURE);
    }

    printf("Processo 1 entrou na região crítica.\n");

    sleep(5);

    operacao.sem_op = 1;
    semaforo = semop(id_semaforo, &operacao, 1);
    if (semaforo == -1) {
        perror("Erro ao incrementar semaforo");
        exit(EXIT_FAILURE);
    }

    printf("Processo 1 saiu da região crítica.\n");

    return 0;
}
