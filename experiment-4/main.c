#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSOS 5
#define TAM_MEMORIA 20

unsigned int bitmap[TAM_MEMORIA];

typedef struct {
    int id;
    int tamanho_processo;
    int posicao_inicio;
    int alocado;
} Processo;

void inicializar_bitmap()
{
    for (int i = 0; i < TAM_MEMORIA; i++) {
        bitmap[i] = 0;
    }
}

void imprimir_bitmap()
{
    for (int i = 0; i < TAM_MEMORIA; i++) {
        printf("%d ", bitmap[i]);
    }

    printf("\n\n");
}

int alocar_processo(Processo *processo)
{
    int tamanho_processo = processo->tamanho_processo;
    int posicao = -1;

    for (int i = 0; i < TAM_MEMORIA - tamanho_processo + 1; i++) {
        int j;

        for (j = 0; j < tamanho_processo; j++) {
            if (bitmap[i + j] != 0) {
                break;
            }
        }

        if (j == tamanho_processo) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        processo->posicao_inicio = posicao;
        processo->alocado = 1;

        for (int i = posicao; i < posicao + tamanho_processo; i++) {
            bitmap[i] = processo->id;
        }
    }

    printf("Processo %d Alocado    | Posição de Início: %d\n", processo->id, processo->posicao_inicio);

    return posicao;
}

void liberar_processo(Processo *processo)
{
    int tamanho_processo = processo->tamanho_processo;
    int posicao = processo->posicao_inicio;

    if (processo->alocado) {
        for (int i = posicao; i < posicao + tamanho_processo; i++) {
            bitmap[i] = 0;
        }

        processo->alocado = 0;
    }

    printf("Processo %d Desalocado | Posição de Início: %d\n", processo->id, processo->posicao_inicio);
}

int main()
{
    inicializar_bitmap();

    Processo processos[NUM_PROCESSOS] = {
        {1, 5, 0, 0},
        {2, 3, 0, 0},
        {3, 4, 0, 0},
        {4, 7, 0, 0},
        {5, 2, 0, 0}};

    printf("\nHistórico de Alocação:\n");

    for (int i = 0; i < NUM_PROCESSOS; i++) {
        if (i == 3) {
            continue;
        }

        alocar_processo(&processos[i]);

        if (i == 2) {
            alocar_processo(&processos[i + 1]);
            liberar_processo(&processos[i]);
        }
    }

    printf("\nProcessos que permaneceram alocados:\n");
    for (int i = 0; i < NUM_PROCESSOS; i++) {
        if (processos[i].alocado) {
            printf("Processo %d | Posição de Início: %d\n", processos[i].id, processos[i].posicao_inicio);
        }
    }

    printf("\nBitmap:\n");
    imprimir_bitmap();

    return 0;
}
