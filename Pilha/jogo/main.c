#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

#include <stdio.h>
#include <time.h>
#include "pilha.h"

char palavrasFacil[20][5] = {"casa", "amor", "vida", "fogo", "agua", "veto", "tera", "luaa", "sola", "nano",
"diaa", "lago", "ruim", "bons", "doce", "sede", "frio", "calo", "pote", "gelo"};

int gameOver = 0;
int gameMode;
Stack pilha;
int aleatorio;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void criarPilha() {
    destroyStack(&pilha);  
    createStack(&pilha);
    aleatorio = rand() % 20;
    for (int i = 0; i < 4; i++) {
        push(&pilha, palavrasFacil[aleatorio][i]);
    }
}

void imprimirPalavra() {
    
    int i = 3;
    while (i > 0){
        printf("Palavra escolhida: %s\n", palavrasFacil[aleatorio]);
        printf("Digite ela ao contrario em %d...", i);
        i--;
        SLEEP(3000);
        clearScreen();
    }
}
  
char resposta[5];
void lerResposta() {
    printf("Palavra ao contrario: ");
    scanf("%4s", resposta);
}

void verificarResposta() {
    char letra;
    char letraCerta;
    for (int i = 0; i < 4; i++){
        letra = resposta[i];
        peek(&pilha, &letraCerta);
        if (letra != letraCerta) {
            printf("Letra incorreta: %c (esperado: %c)\n", letra, letraCerta);
            gameOver = 1;
            break;
        }
        pop(&pilha, &letraCerta);
    }
}

void atualizarEstadoJogo() {

}

int main() {
    srand(time(NULL));

    while(gameOver != 1) {
        criarPilha();
        imprimirPalavra();
        lerResposta();
        verificarResposta();
        atualizarEstadoJogo();
    }

    destroyStack(&pilha);
    //clearScreen();
    printf("Game Over!\n");
    
    return 0;   
}