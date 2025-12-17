#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pilha.h"
#include "input.h"

int main() {
    Stack s;
    createStack(&s);

    int running = 1;
    int frame = 0;
    while (running) {
        printf("Frame atual: %d\n", frame++);

        int input = waitInputForFrame(1000); // Espera por 1 segundo ou até uma tecla ser pressionada

        if (input == -1) {
            printf("voce perdeu");
        }   
        else {
            printf("Tecla pressionada: %c\n", input);
        } 
    }
    destroyStack(&s);
    return 0;
}
