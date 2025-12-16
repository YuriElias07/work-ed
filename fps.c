#include <stdio.h>
#include <unistd.h>   // usleep
#include <time.h>

#define FPS 2
#define FRAME_TIME (1000000 / FPS) // microsegundos

int main() {
    int frame = 0;
    int pos = 0;

    char* num[10] = {"0001","0010","0100","1000","0001","0010","0100","1000"};
        
    while(1){
        // Limpa o terminal
        printf("\033[2J\033[H");

        // "Desenha" o frame
        
        pos = frame%8;
        printf("%s\n", num[pos]);
        printf("Frame: %d\n", frame++);
        printf("Rodando a %d FPS\n", FPS);

        fflush(stdout);

        // Espera o tempo do frame
        usleep(FRAME_TIME);
    }

    return 0;
}
