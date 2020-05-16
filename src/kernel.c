#include "kernel.h"
#include "display.h"
#include "fs/file.h"
#include "disk/disk.h"
#include "memory/kheap.h"
#include "string/string.h"
void main()
{
    // Create the kernels heap
    kheap_init();
    
    // Load all the integrated filesystems
    fs_load();

    // Search for disks and initialize them
    disk_search_and_init();


    {
        int f = fopen("0:/START", 'r');
        if (f < 0)
        {
            panic("Failed to find \"START\" program\r\n");
        }
    }


    // Infinite loop so we never loop off into the universe
    while(1) {

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