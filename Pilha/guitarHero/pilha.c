#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int position;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;


int createStack(Stack* s){
    if (s == NULL) return 0;
    s->top = NULL; 
    s->size = 0;
    return 1;
}

int isEmpty(Stack* s) {
    if (s == NULL) return 0;
    if (s->top == NULL) return 1;
    return 0;
}

int StackSize(Stack* s) {
    return s->size;
}

int push(Stack* s, int position) {
    if (s == NULL) return 0;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        return 0;
    }
    newNode->position = position;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
    return 1;
}

// Remove o elemento do topo da pilha e armazena seu valor em 'position', externamente.
int pop(Stack* s, int* position) {
    if (isEmpty(s)) return 0;

    Node* temp = s->top;
    *position = temp->position;
    s->top = temp->next;
    free(temp);
    s->size--;
    return 1;
}

// Retorna o valor do elemento do topo da pilha sem removê-lo, armazenando em 'position', externamente.
int peek(Stack* s, int* position) {
    if (isEmpty(s)) return 0;
    *position = s->top->position;
    return 1;
}


void destroyStack(Stack* s) {
    Node* current = s->top;
    Node* next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    s->top = NULL;
    s->size = 0;
}