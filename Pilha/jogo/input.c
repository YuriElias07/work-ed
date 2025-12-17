#include <windows.h>
#include <conio.h>
#include "input.h"

int waitInputForFrame(int time_ms) {
    int elapsed = 0;
    const int step = 10;

    while (elapsed < time_ms) {
        if (_kbhit()) {
            int ch = _getch();   // lê UMA tecla válida

            while (_kbhit()) {  // limpa repetições
                _getch();
            }

            return ch;
        }

        Sleep(step);
        elapsed += step;
    }
    return -1;
}
