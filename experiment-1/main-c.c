#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define QUANTUM 3
#define _GNU_SOURCE
void *funcao_thread(void *arg) {
    int id = *(int *)arg;
    int cont = 0;
    while (cont < 10) {
        printf("Thread %d executando...\n", id);
        cont++;
        if (cont % QUANTUM == 0) {
            printf("Thread %d interrompida após quantum\n", id);
            sched_yield();
        }
    }
    printf("Thread %d terminou sua execucao\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    int i, rc;
    for (i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        rc = pthread_create(&threads[i], NULL, funcao_thread, &ids[i]);
        if (rc) {
            printf("Erro ao criar a thread %d\n", i);
            exit(-1);
        }
    }
    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            printf("Erro ao aguardar a thread %d\n", i);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
