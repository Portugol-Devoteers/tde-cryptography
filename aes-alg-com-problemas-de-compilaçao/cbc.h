#ifndef CBC_H
#define CBC_H

#include "includes.h"

int blocksCount(char *text);

int cbc(char *text, unsigned char *keyBytes, unsigned char *iv, short action, unsigned char (*textBlocks)[BLOCK_SIZE]);

#endif /* CBC_H */
