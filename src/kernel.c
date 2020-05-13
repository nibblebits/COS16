#include "kernel.h"
#include "display.h"
#include "fs/file.h"
#include "memory/kheap.h"

void main()
{

    // Create the kernels heap
    kheap_init();

    {
        void *ptr;
        int i = 0;
        for (i = 0; i < 56; i++)
        {
            ptr = kmalloc(512);
            if (ptr == 0)
            {
                panic("Failed to allocate kernel memory\r\n");
            }
        }

        kfree(0x3000);
        ptr = kmalloc(512);
        if (ptr == 0)
        {
            panic("Failed to allocate kernel memory\r\n");
        }
    }

    fs_load();

    print("fuck you");
    {
        int f = fopen("./START", 'w');
        if (f < 0)
        {
            panic("Failed to find \"START\" program\r\n");
        }
    }

    while (1)
    {
    }
}

void panic(char *message)
{
    print("!!!KERNEL PANIC!!!: ");
    print(message);
    while (1)
    {
    }
}