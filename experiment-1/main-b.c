#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void handler(int sig);

int main() {
    int num_processos[3] = {1, 2, 5};
    int i, j, k;
    int pid[8];
    int status;
    int prioridade[8] = {0};
    int max_tempo_exec = 0;
    int max_tempo_exec_index = 0;
    struct sigaction sa;

    srand(time(NULL));

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < num_processos[i]; j++) {
            pid[k] = fork();
            if (pid[k] == 0) {
                printf("Processo filho %d do processo pai %d criado\n", getpid(), getppid());
                int tempo_exec = rand() % 10 + 1;
                printf("Tempo de execução do processo filho %d: %d segundos\n", getpid(), tempo_exec);
                sleep(tempo_exec);
                printf("Processo filho %d do processo pai %d concluído\n", getpid(), getppid());
                exit(0);
            } else {
                prioridade[k] = rand() % 10 + 1;
                printf("Prioridade do processo filho %d do processo pai %d: %d\n", pid[k], getpid(), prioridade[k]);
                k++;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < num_processos[i]; j++) {
            max_tempo_exec = 0;
            max_tempo_exec_index = -1;
            for (k = 0; k < 8; k++) {
                if (getppid() == getpid()) {
                    if (prioridade[k] > 0 && max_tempo_exec < waitpid(pid[k], &status, WNOHANG)) {
                        max_tempo_exec = waitpid(pid[k], &status, WNOHANG);
                        max_tempo_exec_index = k;
                    }
                }
            }
            if (max_tempo_exec_index >= 0) {
                printf("Processo filho %d do processo pai %d interrompido por critério de prioridade\n", pid[max_tempo_exec_index], getpid());
                kill(pid[max_tempo_exec_index], SIGUSR1);
                prioridade[max_tempo_exec_index] = 0;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        if (getppid() == getpid()) {
            waitpid(pid[i], &status, 0);
        }
    }

    return 0;
}

void handler(int sig) {
    printf("Processo filho %d interrompido pelo sinal SIGUSR1\n", getpid());
}
