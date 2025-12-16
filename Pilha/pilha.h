#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int* cordenadas;
    int top;
    int count;
    int capacity;
} Tower;

int createTower(Tower* tower, int mode);
void destroyTower(Tower* tower);
void clearTower(Tower* tower);
int towerIsEmpty(const Tower* tower);
int towerIsFull(const Tower* tower);
int pushTower(Tower* tower, int coord);
int popTower(Tower* tower, int* coord);
int peekTower(const Tower* tower, int* coord);

#endif
