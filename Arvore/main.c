#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

typedef struct Pessoa {
    char nome[MAX_NOME];
    struct Pessoa *pai;
    struct Pessoa *mae;
    struct Pessoa *filhoEsq; // Primeiro filho
    struct Pessoa *irmaoDir; // Próximo irmão
} Pessoa;

Pessoa* criaPessoa(const char *nome) {
    Pessoa *nova = (Pessoa*)malloc(sizeof(Pessoa));
    strcpy(nova->nome, nome);
    nova->pai = NULL;
    nova->mae = NULL;
    nova->filhoEsq = NULL;
    nova->irmaoDir = NULL;
    return nova;
}

void adicionaFilho(Pessoa *pai, Pessoa *mae, Pessoa *filho) {
    filho->pai = pai;
    filho->mae = mae;
    if (pai) {
        if (!pai->filhoEsq) {
            pai->filhoEsq = filho;
        } else {
            Pessoa *atual = pai->filhoEsq;
            while (atual->irmaoDir) atual = atual->irmaoDir;
            atual->irmaoDir = filho;
        }
    }
    if (mae) {
        if (!mae->filhoEsq) {
            mae->filhoEsq = filho;
        } else {
            Pessoa *atual = mae->filhoEsq;
            while (atual->irmaoDir) atual = atual->irmaoDir;
            atual->irmaoDir = filho;
        }
    }
}

void imprimeArvore(Pessoa *p, int nivel) {
    if (!p) return;
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("- %s\n", p->nome);
    imprimeArvore(p->filhoEsq, nivel + 1);
    imprimeArvore(p->irmaoDir, nivel);
}

Pessoa* buscaPessoa(Pessoa *raiz, const char *nome) {
    if (!raiz) return NULL;
    if (strcmp(raiz->nome, nome) == 0) return raiz;
    Pessoa *res = buscaPessoa(raiz->filhoEsq, nome);
    if (res) return res;
    return buscaPessoa(raiz->irmaoDir, nome);
}

void liberaArvore(Pessoa *p) {
    if (!p) return;
    liberaArvore(p->filhoEsq);
    liberaArvore(p->irmaoDir);
    free(p);
}

int main() {
    Pessoa *raiz = NULL;
    int op;
    char nome[MAX_NOME], nomePai[MAX_NOME], nomeMae[MAX_NOME];
    printf("Árvore Genealógica\n");
    do {
        printf("\n1. Adicionar pessoa (sem pais)\n2. Adicionar filho\n3. Mostrar árvore\n0. Sair\nEscolha: ");
        scanf("%d", &op);
        getchar();
        switch(op) {
            case 1:
                printf("Nome da pessoa: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                if (!raiz) {
                    raiz = criaPessoa(nome);
                    printf("Pessoa '%s' adicionada como raiz.\n", nome);
                } else {
                    printf("A raiz já existe!\n");
                }
                break;
            case 2:
                printf("Nome do filho: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Nome do pai (ou deixe vazio): ");
                fgets(nomePai, MAX_NOME, stdin);
                nomePai[strcspn(nomePai, "\n")] = 0;
                printf("Nome da mãe (ou deixe vazio): ");
                fgets(nomeMae, MAX_NOME, stdin);
                nomeMae[strcspn(nomeMae, "\n")] = 0;
                Pessoa *pai = (strlen(nomePai) > 0) ? buscaPessoa(raiz, nomePai) : NULL;
                Pessoa *mae = (strlen(nomeMae) > 0) ? buscaPessoa(raiz, nomeMae) : NULL;
                if (!pai && !mae) {
                    printf("Pai e mãe não encontrados!\n");
                    break;
                }
                Pessoa *filho = criaPessoa(nome);
                adicionaFilho(pai, mae, filho);
                printf("Filho '%s' adicionado.\n", nome);
                break;
            case 3:
                printf("\nÁrvore Genealógica:\n");
                imprimeArvore(raiz, 0);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(op != 0);
    liberaArvore(raiz);
    return 0;
}
