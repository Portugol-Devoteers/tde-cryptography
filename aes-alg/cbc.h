#ifndef CBC_H
#define CBC_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16

int blocksCount(char *text);

int cbc(char *text, unsigned char *keyBytes, unsigned char *iv, short action, unsigned char (*textBlocks)[BLOCK_SIZE]);

#endif /* CBC_H */
