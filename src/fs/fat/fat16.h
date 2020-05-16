#include "fs/file.h"
#include "types.h"


#define COS16_FAT16_SIGNATURE 0x29
struct filesystem* fat16_init();