#include "file.h"
#include "config.h"
#include "kernel.h"
#include "memory/memory.h"
#include "fat/fat16.h"
#include "disk/disk.h"
#include "string/string.h"
#include "status.h"

struct filesystem *filesystems[COS16_MAX_FILESYSTEMS];

static struct filesystem **fs_get_free_filesystem()
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
    struct filesystem **fs;
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
    print(" initialized\r\n");
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

/**
 * 
 * Tests the given filename to see if the path is a valid format
 * \warning This function does not test if the path exists or not
 * Valid paths
 * 0:/
 * 0:/testing/abc
 * 1:/abc/testing
 * 
 * Invalid paths
 * A:/abc
 * B:/
 */
static int fs_valid_path_format(char *filename)
{
    int len = strnlen(filename, COS16_MAX_PATH);
    return len >= 3 && isdigit(filename[0]) && memcmp(&filename[1], ":/", 2) == 0;
}

static int fs_get_drive_by_path(char *filename)
{
    int len = strnlen(filename, COS16_MAX_PATH);
    if (!fs_valid_path_format(filename))
    {
        return -COS16_BAD_PATH;
    }

    return tonumericdigit(filename[0]);
}

int fopen(char *filename, char mode)
{
    int i = 0;
    int drive_no = fs_get_drive_by_path(filename);
    if (drive_no < 0)
    {
        return drive_no;
    }


    {
        char* start_of_relative_path = &filename[2];
        struct disk *disk = disk_get(drive_no);
        
        if (!disk)
        {
            return -COS16_INVALID_DRIVE;
        }

        print("testing");
        return filesystems[0]->open(disk, "abc", mode);
    }
}

struct filesystem *fs_resolve(struct disk *disk)
{
    struct filesystem *fs = 0;
    int i;
    for (i = 0; i < COS16_MAX_FILESYSTEMS; i++)
    {
        if (filesystems[i] != 0 && filesystems[i]->resolve(disk) == 0)
        {
            fs = filesystems[i];
            break;
        }
    }

    return fs;
}