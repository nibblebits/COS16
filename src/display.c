#include "display.h"
void print(char* message)
{
    int i = 0;
    for (i = 0; ; i++)
    {
        if (message[i] == 0)
            break;

        putchar(message[i]);
    }
}