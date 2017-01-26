#include <gctypes.h>

u8 gMode __attribute__((section(".data"))) = 0;
u8 gTarget __attribute__((section(".data"))) = 0;
char gFolderPath[1024][256] __attribute__((section(".data"))) = { "\0" };
int gFolderSequence[1024] __attribute__((section(".data"))) = { 0 };
