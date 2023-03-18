#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSOS 100

struct processo {
    int pid;
    char nome[50];
    int prioridade;
    int tempo_execucao;
};

struct bcp {
    int estado;
    struct processo proc;
};

struct bcp tabela_processos[MAX_PROCESSOS];

void inicializar_tabela_processos() {
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        tabela_processos[i].estado = 0;
    }
}

int adicionar_processo(int pid, char *nome, int prioridade, int tempo_execucao) {
    int i;
    for (i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].estado == 0) {
            tabela_processos[i].estado = 1;
            tabela_processos[i].proc.pid = pid;
            strcpy(tabela_processos[i].proc.nome, nome);
            tabela_processos[i].proc.prioridade = prioridade;
            tabela_processos[i].proc.tempo_execucao = tempo_execucao;
            return i;
        }
    }
    return -1;
}

int remover_processo(int pid) {
    int i;
    for (i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].estado == 1 && tabela_processos[i].proc.pid == pid) {
            tabela_processos[i].estado = 0;
            return 0;
        }
    }
    return -1;
}

void listar_processos() {
    printf("PID\tNome\tPrioridade\tTempo Execucao\n");
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].estado == 1) {
            printf("%d\t%s\t%d\t\t%d\n", tabela_processos[i].proc.pid, tabela_processos[i].proc.nome, tabela_processos[i].proc.prioridade, tabela_processos[i].proc.tempo_execucao);
        }
    }
}

void função_1() {
    inicializar_tabela_processos();

    adicionar_processo(1, "processo1", 2, 10);
    adicionar_processo(2, "processo2", 1, 5);
    adicionar_processo(3, "processo3", 3, 15);

    listar_processos();

    remover_processo(2);

    listar_processos();
}

int main() {
    função_1();
    return 0;
}
