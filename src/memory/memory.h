#ifndef MEMORY_H
#define MEMORY_H

void memset(char* ptr, char v, int len);
void* memcpy (void *dest,  void *src, int len);
int memcmp (char* s1, char* s2, int count);

#endif