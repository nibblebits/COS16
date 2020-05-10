#include "fat16.h"
#include "memory/memory.h"
#include "string/string.h"
#include "status.h"

static struct filesystem fat16_fs;

void* fat16_open(char* filename, char mode)
{
    // Read only filesystem
    if (mode != 'r')
    {
        return -COS16_FS_FILE_READ_ONLY_ERROR;
    }

    return COS16_ALL_OK;
}

struct filesystem* fat16_init()
{
    fat16_fs.open = fat16_open;
    strncpy(fat16_fs.name, "FAT16", sizeof(fat16_fs.name));
    return &fat16_fs;
}