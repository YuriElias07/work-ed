#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* cordenadas;
    int top;
    int qtd;
} Tower;

void pushTower(){
    
}

//a torre é criada com um tamanho predefinido a partir da dificuldade
void createTower(Tower* p1, int mode){
    switch(mode){
        case 0:
            p1->cordenadas = malloc(4*sizeof(int));
            break;
        case 1:
            p1->cordenadas = malloc(7*sizeof(int));
            break;
        case 2:
            p1->cordenadas = malloc(10*sizeof(int));
            break;
        default:
            printf("opção invalida");
            return;
    }
    
    
    p1->top = -1;
    p1->qtd = 0;
    printf("torre criada com sucesso");
}



int main()
{
    

    return 0;
}