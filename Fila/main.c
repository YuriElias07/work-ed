#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 52
#define MAX_NOME 20

typedef struct Carta {
    char nome[MAX_NOME];
    struct Carta *prox;
} Carta;

typedef struct {
    Carta *inicio;
    Carta *fim;
    int tamanho;
} Fila;

void inicializaFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

void enfileira(Fila *f, char *nome) {
    Carta *nova = (Carta*)malloc(sizeof(Carta));
    strcpy(nova->nome, nome);
    nova->prox = NULL;
    if (filaVazia(f)) {
        f->inicio = nova;
    } else {
        f->fim->prox = nova;
    }
    f->fim = nova;
    f->tamanho++;
}

void desenfileira(Fila *f) {
    if (filaVazia(f)) {
        printf("A fila está vazia!\n");
        return;
    }
    Carta *remover = f->inicio;
    f->inicio = remover->prox;
    printf("Carta '%s' removida do topo da fila.\n", remover->nome);
    free(remover);
    f->tamanho--;
    if (f->inicio == NULL) f->fim = NULL;
}

void mostraFila(Fila *f) {
    Carta *atual = f->inicio;
    printf("Cartas na fila: ");
    while (atual != NULL) {
        printf("[%s] ", atual->nome);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    Fila fila;
    inicializaFila(&fila);
    int op;
    char nome[MAX_NOME];
    printf("Jogo de Cartas: Compra e Descarte (Fila)\n");
    do {
        printf("\n1. Comprar carta\n2. Descartar carta do topo\n3. Mostrar fila\n0. Sair\nEscolha: ");
        scanf("%d", &op);
        getchar();
        switch(op) {
            case 1:
                printf("Nome da carta: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                enfileira(&fila, nome);
                break;
            case 2:
                desenfileira(&fila);
                break;
            case 3:
                mostraFila(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(op != 0);
    // Limpa fila ao sair
    while (!filaVazia(&fila)) desenfileira(&fila);
    return 0;
}
