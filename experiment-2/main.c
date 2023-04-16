#include <stdio.h>

void banker(int n, int m, int existent[], int available[], int allocation[][m], int request[][m]) {
    int i, j, k;

    int executed_processes[n], execution_order[n], current_process_index = 0;

    for (k = 0; k < n; k++) {
        executed_processes[k] = 0; // Inicializa todos os processos como não executados
    }

    int actual_process_need[n][m];

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            actual_process_need[i][j] = request[i][j] - allocation[i][j]; // Calcula a necessidade real de cada processo
        }
    }

    int x = 0;

    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (executed_processes[i] == 0) {
                int is_executable = 1;

                for (j = 0; j < m; j++) {
                    if (actual_process_need[i][j] > available[j]) { // Verifica se o processo requisita mais recursos do que o disponível
                        is_executable = 0;
                        break;
                    }
                }

                if (is_executable == 1) {
                    execution_order[current_process_index++] = i; // Adiciona o processo à ordem de execução

                    for (x = 0; x < m; x++) {
                        available[x] += allocation[i][x]; // Libera os recursos alocados pelo processo
                    }

                    executed_processes[i] = 1; // Marca o processo como executado
                }
            }
        }
    }

    int safe_state = 1;

    for (int i = 0; i < n; i++) {
        if (executed_processes[i] == 0) {
            safe_state = 0;
            printf("Estado inseguro!");
            break;
        }
    }

    if (safe_state == 1) {
        printf("Estado seguro\n");
        printf("Ordem de execução:");

        char process_name;

        for (i = 0; i < n - 1; i++) {
            process_name = execution_order[i] + 65;
            printf(" %c >", process_name);
        }

        process_name = execution_order[n - 1] + 65;
        printf(" %c", process_name);
    }

    printf("\n");
}

int main() {
    int n = 10;
    int m = 5;

    int existent[5] = {10, 11, 8, 12, 7};

    int available[5] = {6, 3, 0, 3, 2};

    int allocation[10][5] = {
        {0, 1, 1, 2, 0},
        {1, 1, 3, 3, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 1, 2, 1, 2},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {1, 2, 1, 0, 0}};

    int request[10][5] = {
        {0, 3, 0, 2, 1},
        {2, 0, 1, 1, 0},
        {1, 1, 8, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 2},
        {4, 1, 0, 1, 0},
        {0, 0, 3, 1, 0},
        {1, 0, 0, 4, 1},
        {1, 1, 1, 5, 0}};

    printf("Matriz de alocação corrente:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    printf("Matriz de requisição:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", request[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    printf("Vetor de recursos existentes:\n");

    for (int i = 0; i < m; i++) {
        printf("%d ", existent[i]);
    }

    printf("\n\n");

    banker(n, m, existent, available, allocation, request);

    return 0;
}
