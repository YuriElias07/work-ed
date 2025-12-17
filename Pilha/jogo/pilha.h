#ifndef PILHA_H
#define PILHA_H

typedef struct Node{
    int position;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;

int createStack(Stack* s);
int isEmpty(Stack* s);
int StackSize(Stack* s);
int push(Stack* s, char letra);
int pop(Stack* s, char* letra);
int peek(Stack* s, char* letra);
void destroyStack(Stack* s);

#endif