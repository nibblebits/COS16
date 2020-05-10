#ifndef FILE_H
#define FILE_H

typedef void*(*FS_OPEN_FUNCTION)(char* filename, char mode);
struct filesystem
{
    FS_OPEN_FUNCTION open;
    char name[20];
};

void fs_load();
int fopen(char* filename, char mode);
void fs_insert_filesystem(struct filesystem* filesystem);

#endif