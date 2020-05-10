#include "file.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
#include "fat/fat16.h"
#include "stdarg.h"

struct filesystem* filesystems[COS16_MAX_FILESYSTEMS];

static struct filesystem** fs_get_free_filesystem()
{
    int i = 0;
    for (i = 0; i < COS16_MAX_FILESYSTEMS; i++)
    {
        if (filesystems[i] == 0)
        {
            return &filesystems[i];
        }
    }

    return 0;
}

void fs_insert_filesystem(struct filesystem *filesystem)
{  
    struct filesystem** fs;
    if (filesystem == 0)
    {
        panic("NULL filesystem provided");
    }

    fs = fs_get_free_filesystem();
    if (!fs)
    {
        panic("No more filesystem slots available, failed to register filesystem");
    }

    *fs = filesystem;
    print("filesystem ");
    print(filesystem->name);
    print(" initialized");
}

/**
 * Loads statically compiled filesystems
 */
static void fs_static_load()
{
    fs_insert_filesystem(fat16_init());
}

void fs_load()
{
    memset(filesystems, 0, sizeof(filesystems));
    fs_static_load();
}

int fopen(char *filename, char mode)
{
    int i = 0;
    for (i = 0; i < COS16_MAX_FILESYSTEMS; i++)
    {
        if (filesystems[i] != 0)
        {
            return filesystems[i]->open(filename, mode);
        }
    }
    return 0;
}