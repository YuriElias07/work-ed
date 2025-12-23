#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#include <stdio.h>

#ifndef _WIN32
void setRawMode(int enable)
{
    static struct termios old;
    struct termios new;

    if (enable)
    {
        tcgetattr(0, &old);
        new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &new);
    }
    else
    {
        tcsetattr(0, TCSANOW, &old);
    }
}
#endif

// Retorna a tecla pressionada ou -1 se o tempo acabar
int getKeyWithTimeout(int timeout_ms)
{
    int elapsed = 0;

#ifndef _WIN32
    setRawMode(1);
#endif

    while (elapsed < timeout_ms)
    {

#ifdef _WIN32
        if (_kbhit())
        {
#ifndef _WIN32
            setRawMode(0);
#endif
            printf("\a");// talvez não funcione em macos
            return _getch();
        }
        Sleep(10);

#else
        char c;
        if (read(0, &c, 1) == 1)
        {
            setRawMode(0);
            return c;
        }
        usleep(10000);
#endif

        elapsed += 10;
    }

#ifndef _WIN32
    setRawMode(0);
#endif

    return -1;
}

