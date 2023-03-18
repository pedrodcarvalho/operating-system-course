#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSOS 5

typedef struct {
    int pid;
    int prioridade;
    int tempo_execucao;
} processo;

int main() {
    processo processos[NUM_PROCESSOS] = {
        {1, 2, 5},
        {2, 1, 3},
        {3, 3, 8},
        {4, 4, 4},
        {5, 2, 6}};
    int i, j, tempo_total = 0;
    processo aux;
    for (i = 0; i < NUM_PROCESSOS; i++) {
        for (j = i + 1; j < NUM_PROCESSOS; j++) {
            if (processos[i].prioridade < processos[j].prioridade) {
                aux = processos[i];
                processos[i] = processos[j];
                processos[j] = aux;
            }
        }
    }
    for (i = 0; i < NUM_PROCESSOS; i++) {
        printf("Processo %d (prioridade %d, tempo de execucao %d) executando...\n", processos[i].pid, processos[i].prioridade, processos[i].tempo_execucao);
        tempo_total += processos[i].tempo_execucao;
    }
    printf("Tempo total de execucao: %d\n", tempo_total);
    return 0;
}
