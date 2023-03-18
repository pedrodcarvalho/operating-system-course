#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void imprimir_cabecalho() {
    printf("+------+---------+-----------------+------------------+\n");
    printf("| Name | Process | Início do tempo | Término do tempo |\n");
    printf("+------+---------+-----------------+------------------+\n");
}

void imprimir_processo(int pid, char process_name[100]) {
    if (strcmp(process_name, "Bubble") == 0) {
        printf("|%s| %7d |   %10ld ms |    %10ld ms |\n", process_name, pid, clock() * 1000 / CLOCKS_PER_SEC, (clock() + 2) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("|%s | %7d |   %10ld ms |    %10ld ms |\n", process_name, pid, clock() * 1000 / CLOCKS_PER_SEC, (clock() + 2) * 1000 / CLOCKS_PER_SEC);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;

    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    int j;

    for (j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void bubble_sort(int arr[], int num) {
    int x, y, temp;

    x = 0;

    while (x < num) {
        y = 0;

        while (y < num - x) {
            if (arr[y] > arr[y + 1]) {
                temp = arr[y];
                arr[y] = arr[y + 1];
                arr[y + 1] = temp;
            }

            y++;
        }

        x++;
    }
}

int main() {
    int pid;
    int i, status;
    char process_name[3][100] = {"Merge", "Quick", "Bubble"};

    int arr[10000];

    srand(time(NULL));

    for (i = 0; i < 10000; i++) {
        arr[i] = rand() % 100;
    }

    imprimir_cabecalho();

    for (i = 0; i < 3; i++) {
        pid = fork();

        if (pid == -1) {
            printf("Erro ao criar processo filho.\n");
            exit(1);
        } else if (pid == 0) {
            sleep(2);
            printf("Processo filho %d concluído.\n", getpid());
            exit(0);
        } else {
            if (i == 0) {
                merge_sort(arr, 0, 9999);
            } else if (i == 1) {
                quick_sort(arr, 0, 9999);
            } else if (i == 2) {
                bubble_sort(arr, 9999);
            }

            imprimir_processo(pid, process_name[i]);
            printf("+------+---------+-----------------+------------------+\n");
            printf("|Processo pai criou processo filho %d.             |\n", pid);
            printf("+------+---------+-----------------+------------------+\n");
        }
    }

    for (i = 0; i < 3; i++) {
        pid = wait(&status);

        printf("Processo filho %d terminou com status %d.\n", pid, WEXITSTATUS(status));
    }

    printf("Todos os processos terminaram.\n");

    return 0;
}
