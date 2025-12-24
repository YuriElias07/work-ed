#ifdef _WIN32// adaptado para windows e linux 
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

#define TimerFacil 2000
#define TimerMedio 1000
#define TimerDificil 500

#define FACIL 15
#define MEDIO 25
#define DIFICIL 35
int gameOver = 1;
int lifes = 3;
int points = 0;
int minuspoints;
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
    printf("Vidas: %d   Pontuacao: %d\n", lifes, points);

    int position;
    peek(&pilha, &position);
    printTelaBotao(position);
}

void lerResposta(int gameMode) {
    int timer;
    if(gameMode == 1) timer = TimerFacil;
    else if(gameMode == 2) timer = TimerMedio;
    else if(gameMode == 3) timer = TimerDificil;

    

    int position;
    pop(&pilha, &position);//ja remove o elemento do topo da pilha
    int resposta = getKeyWithTimeout(timer, &minuspoints);
    if (resposta == -1 || resposta - '1' != position) {
        //printf("Resposta incorreta ou tempo esgotado!\n");
        lifes--;
        return;
    } else if(isEmpty(&pilha)) {
        clearScreen();
        points += timer - minuspoints;
        printf("Voce venceu o jogo!\n");
        SLEEP(3000);
        printf("Pontuacao final: %d", points);
        SLEEP(5000);
        gameOver = 0;
        return;
    }
    points += timer - minuspoints;

}

void apresentarJogo(){
    clearScreen();
    printf("\t- GuitarHero -\n\n");
    SLEEP(2000);
    printf("~ Feito por Joao Victor, Otavio augusto e Yuri Elias.\n\n");
    SLEEP(3000);
    printf("* Use as teclas 1 2 3 4 para acertar as notas.\n");
    SLEEP(6000);
    clearScreen();

}

void atualizarEstadoJogo() {
    if (lifes == 0) {
        gameOver = 0;
        clearScreen();
        printf("Suas vidas acabaram!\n\n");
        SLEEP(2000);
        printf("Pontuacao final: %d", points);
        SLEEP(5000);
        clearScreen();
    }
}

int main() {
    srand(time(NULL));

    apresentarJogo();

    int gameMode;
    printf("Escolha o modo de jogo:\n1. Facil\n2. Medio\n3. Dificil\n");
    scanf("%d", &gameMode);

    criarPilha(gameMode);
    printf("jogo iniciado!\n");
    SLEEP(4000);
    clearScreen();
    while(gameOver){
        imprimirPosition();
        lerResposta(gameMode);
        //verificarResposta(); ja verifica na lerResposta
        atualizarEstadoJogo(); 
        clearScreen();
    }

    return 0;
}