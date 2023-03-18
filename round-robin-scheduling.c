#include <stdio.h>

#define QUANTUM 2

typedef struct {
    int pid;
    int tempo_restante;
} Processo;

void round_robin(Processo processos[], int num_processos) {
    int tempo_restante_total = 0;
    int tempo_atual = 0;
    int processos_terminados[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < num_processos; i++) {
        tempo_restante_total += processos[i].tempo_restante;
    }

    printf("+-------+-------+--------------+");
    printf("\n|Quantum = %d                   |", QUANTUM);
    printf("\n+-------+-------+--------------+");
    printf("\n|PID\t|Tempo\t|Tempo restante|");
    printf("\n+-------+-------+--------------+");

    while (tempo_restante_total > 0) {
        for (int i = 0; i < num_processos; i++) {
            if (processos[i].tempo_restante > 0) {
                if (processos[i].tempo_restante > QUANTUM) {
                    tempo_atual += QUANTUM;
                    processos[i].tempo_restante -= QUANTUM;
                } else {
                    tempo_atual += processos[i].tempo_restante;
                    processos[i].tempo_restante = 0;
                }

                printf("\n|%d\t|%d\t|%d             |", processos[i].pid, tempo_atual, processos[i].tempo_restante);
                printf("\n+-------+-------+--------------+");
            } else {
                if (processos_terminados[i] == 0) {
                    printf("\n|Processo %d terminou           |", processos[i].pid);
                    printf("\n+-------+-------+--------------+");
                    processos_terminados[i] = processos[i].pid;
                }
            }

            tempo_restante_total = 0;

            for (int i = 0; i < num_processos; i++) {
                tempo_restante_total += processos[i].tempo_restante;
            }
        }
    }

    printf("\n|Processo %d terminou           |", processos[4].pid);
    printf("\n+-------+-------+--------------+");
    printf("\n|Todos os processos terminaram |\n");
    printf("+-------+-------+--------------+\n");

    return;
}

int main() {
    Processo processos[5];

    for (int i = 0; i < 5; i++) {
        processos[i].pid = i + 1;
        processos[i].tempo_restante = 2 * i + 1;
    }

    round_robin(processos, 5);

    return 0;
}
