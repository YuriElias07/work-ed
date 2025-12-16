#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

static int resolve_capacity(int mode) {
    switch (mode) {
        case 0:
            return 4;
        case 1:
            return 7;
        case 2:
            return 10;
        default:
            return -1;
    }
}

int createTower(Tower* tower, int mode) {
    if (!tower) {
        return 0;
    }

    int capacity = resolve_capacity(mode);
    if (capacity <= 0) {
        fprintf(stderr, "opção invalida\n");
        return 0;
    }

    tower->cordenadas = malloc(sizeof(int) * capacity);
    if (!tower->cordenadas) {
        fprintf(stderr, "falha ao alocar memoria para a torre\n");
        return 0;
    }

    tower->capacity = capacity;
    clearTower(tower);
    printf("torre criada com sucesso (%d blocos)\n", capacity);
    return 1;
}

void destroyTower(Tower* tower) {
    if (!tower) {
        return;
    }

    free(tower->cordenadas);
    tower->cordenadas = NULL;
    tower->capacity = 0;
    tower->top = -1;
    tower->count = 0;
}

void clearTower(Tower* tower) {
    if (!tower) {
        return;
    }

    tower->top = -1;
    tower->count = 0;
}

int towerIsEmpty(const Tower* tower) {
    return !tower || tower->count == 0;
}

int towerIsFull(const Tower* tower) {
    return tower && tower->count == tower->capacity;
}

int pushTower(Tower* tower, int coord) {
    if (!tower || towerIsFull(tower)) {
        return 0;
    }

    tower->top++;
    tower->cordenadas[tower->top] = coord;
    tower->count++;
    return 1;
}

int popTower(Tower* tower, int* coord) {
    if (!tower || towerIsEmpty(tower)) {
        return 0;
    }

    if (coord) {
        *coord = tower->cordenadas[tower->top];
    }

    tower->top--;
    tower->count--;
    return 1;
}

int peekTower(const Tower* tower, int* coord) {
    if (towerIsEmpty(tower)) {
        return 0;
    }

    if (coord) {
        *coord = tower->cordenadas[tower->top];
    }
    return 1;
}
