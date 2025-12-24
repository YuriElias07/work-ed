#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

#include <stdio.h>
#include <time.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

"╔════════════════════════════╗\n"
"║  ░░        ░░        ░░    ║\n"
"║  ░░        ░░        ░░    ║\n"
"║  ██        ██        ██    ║\n"
"║  [#]       [ ]       [ ]   ║\n"
"╚════════════════════════════╝\n"


char telaBotao1[] =
"====================\n"
"[#]   [ ]   [ ]   [ ]\n"
"====================\n";

char telaBotao2[] =
"====================\n"
"[ ]   [#]   [ ]   [ ]\n"
"====================\n";

char telaBotao3[] =
"====================\n"
"[ ]   [ ]   [#]   [ ]\n"
"====================\n";

char telaBotao4[] =
"====================\n"
"[ ]   [ ]   [ ]   [#]\n"
"====================\n";

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

int main() {
    srand(time(NULL));
    int botton; 

    while(1) {
        int botton = rand() % 4;    
        clearScreen();
        printTelaBotao(botton);
        SLEEP(500);
        
    }


    return 0;
}