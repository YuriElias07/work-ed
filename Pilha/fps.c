#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/time.h>

#include "pilha.h"

#define MICROSECONDS_PER_SECOND 1000000
#define COLUMNS 4

static struct termios original_termios;
static int raw_mode_enabled = 0;

static void clearScreen(void) {
    printf("\033[2J\033[H");
}

static void disableRawMode(void) {
    if (raw_mode_enabled) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
        raw_mode_enabled = 0;
    }
}

static int enableRawMode(void) {
    if (tcgetattr(STDIN_FILENO, &original_termios) == -1) {
        return 0;
    }

    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return 0;
    }

    raw_mode_enabled = 1;
    atexit(disableRawMode);
    return 1;
}

static int waitInputForFrame(int microseconds) {
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    struct timeval tv;
    tv.tv_sec = microseconds / 1000000;
    tv.tv_usec = microseconds % 1000000;

    int ready = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &tv);
    if (ready <= 0) {
        return -1;
    }

    char ch;
    ssize_t bytes_read = read(STDIN_FILENO, &ch, 1);
    if (bytes_read <= 0) {
        return -1;
    }

    return (int)ch;
}

static void consumeLine(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int promptDifficulty(void) {
    int mode;
    while (1) {
        printf("Escolha a dificuldade (0=Fácil, 1=Médio, 2=Difícil): ");
        fflush(stdout);
        if (scanf("%d", &mode) == 1 && mode >= 0 && mode <= 2) {
            consumeLine();
            return mode;
        }

        printf("Valor inválido. Tente novamente.\n");
        consumeLine();
    }
}

static void waitForEnter(void) {
    printf("Pressione Enter para iniciar...");
    fflush(stdout);
    consumeLine();
}

static int startingLives(int mode) {
    switch (mode) {
        case 0:
            return 5;
        case 1:
            return 4;
        case 2:
            return 3;
        default:
            return 3;
    }
}

static int randomColumn(void) {
    return rand() % COLUMNS;
}

static void fillTowerRandom(Tower* tower) {
    if (!tower) {
        return;
    }

    while (!towerIsFull(tower)) {
        pushTower(tower, randomColumn());
    }
}

static void drawStackPreview(const Tower* tower) {
    printf("Pilha (topo -> base): ");
    if (towerIsEmpty(tower)) {
        printf("vazia\n\n");
        return;
    }

    for (int i = tower->top; i >= 0; --i) {
        printf("%d", tower->cordenadas[i] + 1);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\nPróximos alvos armazenados: %d\n\n", tower->count);
}

static int fpsForDifficulty(int mode) {
    switch (mode) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        default:
            return 1;
    }
}

static void drawBoard(int column, int frame, int score, int lives, const Tower* tower, int fps) {
    clearScreen();
    printf("Frame: %d | Pontos: %d | Vidas: %d | Velocidade: %d FPS\n", frame, score, lives, fps);
    printf("Derrote o inimigo apertando 1-4 (pressione 'q' para sair)\n\n");
    printf("+---+---+---+---+\n|");
    for (int col = 0; col < COLUMNS; ++col) {
        printf(" %c |", col == column ? 'X' : ' ');
    }
    printf("\n+---+---+---+---+\n  1   2   3   4\n\n");
    drawStackPreview(tower);
    printf("Entrada em tempo real: ");
    fflush(stdout);
}

int main(void) {
    srand((unsigned int)time(NULL));

    int mode = promptDifficulty();
    int fps = fpsForDifficulty(mode);
    int frameDelay = MICROSECONDS_PER_SECOND / fps;

    printf("\nUse as teclas 1-4 para atingir a coluna destacada antes do tempo acabar.\n");
    printf("Os próximos inimigos ficam guardados na pilha (topo = próximo a aparecer).\n");
    printf("Você possui um número limitado de vidas, que varia com a dificuldade escolhida.\n");
    printf("Velocidade configurada: %d alvo(s) por segundo.\n\n", fps);
    waitForEnter();

    Tower tower = {0};
    if (!createTower(&tower, mode)) {
        return 1;
    }

    fillTowerRandom(&tower);

    if (!enableRawMode()) {
        fprintf(stderr, "Não foi possível configurar o terminal para leitura em tempo real.\n");
        destroyTower(&tower);
        return 1;
    }

    int lives = startingLives(mode);
    int frame = 0;
    int score = 0;
    int running = 1;

    while (running && lives > 0) {
        int column;
        if (!popTower(&tower, &column)) {
            fillTowerRandom(&tower);
            continue;
        }

        drawBoard(column, frame, score, lives, &tower, fps);
        int input = waitInputForFrame(frameDelay);

        if (input == 'q' || input == 'Q') {
            running = 0;
        } else if (input >= '1' && input <= '4') {
            int chosen = input - '1';
            if (chosen == column) {
                score += 10;
            } else {
                lives--;
            }
        } else if (input == -1) {
            lives--;
        } else {
            lives--;
        }

        if (!towerIsFull(&tower)) {
            pushTower(&tower, randomColumn());
        }

        frame++;
    }

    disableRawMode();
    clearScreen();
    printf("Fim de jogo! Pontuação final: %d | Frames jogados: %d\n", score, frame);
    if (lives <= 0) {
        printf("Suas vidas acabaram. Tente novamente para dominar a pilha!\n");
    } else {
        printf("Partida encerrada pelo jogador.\n");
    }
    destroyTower(&tower);
    return 0;
}
