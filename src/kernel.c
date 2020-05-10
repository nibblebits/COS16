#include "kernel.h"
#include "display.h"
#include "fs/file.h"

void main()
{
    fs_load();

    {
        int f = fopen("./START", 'w');
        if (f < 0)
        {
            panic("Failed to find \"START\" program");
        }
    }
}

void panic(char *message)
{
    print(message);
    while (1)
    {
    }
}