#include "memory.h"
void memset(char* ptr, char v, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        ptr[i] = v;
    }
}

int memcmp (char* s1, char* s2, int count)
{
  while (count-- > 0)
    {
      if (*s1++ != *s2++)
	  return s1[-1] < s2[-1] ? -1 : 1;
    }
  return 0;
}


void* memcpy (void *dest,  void *src, int len)
{
  char *d = dest;
  char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}
