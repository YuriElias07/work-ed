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
#include "receptTImer.h"

#define Timer 3000
#define FACIL 15
#define MEDIO 25
#define DIFICIL 35
int gameOver = 1;
Stack pilha;

//telas para simular frames do jogo
char telaBotao1[] =
"==============================================\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|      [###]     [ ]      [ ]      [ ]       |\n"
"==============================================\n";


char telaBotao2[] =
"==============================================\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|       [ ]     [###]     [ ]      [ ]       |\n"
"==============================================\n";

char telaBotao3[] =
"==============================================\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|       [ ]      [ ]     [###]     [ ]       |\n"
"==============================================\n";

char telaBotao4[] =
"==============================================\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|        |        |        |        |        |\n"
"|       [ ]      [ ]      [ ]     [###]      |\n"
"==============================================\n";

void printTelaBotao(int botton) {
    switch(botton) {
        case 0:
            printf("%s", telaBotao1);
            break;
        case 1:
            printf("%s", telaBotao2);
            break;
        case 2:
            printf("%s", telaBotao3);
            break;
        case 3:
            printf("%s", telaBotao4);
            break;
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void criarPilha(int gameMode) {
    if(gameMode == 1) gameMode = FACIL;
    else if(gameMode == 2) gameMode = MEDIO;
    else if(gameMode == 3) gameMode = DIFICIL;

    destroyStack(&pilha);
    createStack(&pilha);
    int position;
    for(int i = 0; i < gameMode; i++){
        position = rand() % 4;
        push(&pilha, position);
    }
}


void imprimirPosition() {
    int position;
    peek(&pilha, &position);
    printTelaBotao(position);
}

void lerResposta() {
    int position;
    pop(&pilha, &position);//ja remove o elemento do topo da pilha
    int resposta = getKeyWithTimeout(Timer);
    if (resposta == -1 || resposta - '1' != position) {
        printf("Resposta incorreta ou tempo esgotado!\n");
        SLEEP(3000);
        gameOver = 0;
    } else if(isEmpty(&pilha)) {
        printf("Voce venceu o jogo!\n");
        SLEEP(3000);
        gameOver = 0;
    }

}

int main() {
    srand(time(NULL));

    int gameMode;
    printf("Escolha o modo de jogo:\n1. Facil\n2. Medio\n3. Dificil\n");
    scanf("%d", &gameMode);

    criarPilha(gameMode);
    printf("jogo iniciado!\n");
    SLEEP(4000);
    clearScreen();
    while(gameOver){
        imprimirPosition();
        lerResposta();
        //verificarResposta(); ja verifica na lerResposta
        //atualizarEstadoJogo(); ja atualiza na lerResposta
        clearScreen();
    }

    return 0;
}