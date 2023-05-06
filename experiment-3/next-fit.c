#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCESSOS 5
#define TAM_MEMORIA 100

int memoria[TAM_MEMORIA];
int ultima_posicao = 0; // Variável global para guardar a última posição disponível

typedef struct {
    int id;
    int tamanho;
} Processo;

void inicializar_memoria()
{
    for (int i = 0; i < TAM_MEMORIA; i++) {
        memoria[i] = -1;
    }
}

void imprimir_memoria()
{
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (i % 10 == 0) {
            printf("\n");
        }
        printf("%d\t", memoria[i]);
    }
    printf("\n\n");
}

int encontrar_maior_espaco_livre(int tamanho_processo)
{
    int espaco_livre_atual = 0;
    int maior_espaco_livre = 0;
    int posicao_maior_espaco_livre = -1;

    for (int i = ultima_posicao; i < TAM_MEMORIA; i++) {
        if (memoria[i] == -1) {
            espaco_livre_atual++;
        }
        else {
            if (espaco_livre_atual > maior_espaco_livre && espaco_livre_atual >= tamanho_processo) {
                maior_espaco_livre = espaco_livre_atual;
                posicao_maior_espaco_livre = i - espaco_livre_atual;
            }
            espaco_livre_atual = 0;
        }
    }

    if (espaco_livre_atual > maior_espaco_livre && espaco_livre_atual >= tamanho_processo) {
        maior_espaco_livre = espaco_livre_atual;
        posicao_maior_espaco_livre = TAM_MEMORIA - espaco_livre_atual;
    }

    ultima_posicao = posicao_maior_espaco_livre;
    return posicao_maior_espaco_livre;
}

int alocar_processo(Processo processo)
{
    int posicao_inicio = encontrar_maior_espaco_livre(processo.tamanho);
    if (posicao_inicio == -1) {
        return -1;
    }
    for (int i = posicao_inicio; i < posicao_inicio + processo.tamanho; i++) {
        memoria[i] = processo.id;
    }
    return posicao_inicio;
}

int main()
{
    inicializar_memoria();

    Processo processos[NUM_PROCESSOS] = {
        {1, 30},
        {2, 20},
        {3, 10},
        {4, 40},
        {5, 25}};

    printf("Memoria antes da alocacao:\n");
    imprimir_memoria();

    for (int i = 0; i < NUM_PROCESSOS; i++) {
        int posicao_inicio = alocar_processo(processos[i]);
        if (posicao_inicio == -1) {
            printf("Nao foi possivel alocar o processo %d\n", processos[i].id);
        }
        else {
            printf("Processo %d alocado na posicao %d\n", processos[i].id, posicao_inicio);
        }
        imprimir_memoria();
    }

    return 0;
}
