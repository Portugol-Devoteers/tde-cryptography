#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core.h"
#include "derive-key.h"
#include "utils.h"
#include "to-blocks.h"
#include "expand-key.h"

short getRounds(short keyLength)
{
  switch (keyLength)
  {
  case 16:
    return 10;
  case 24:
    return 12;
  case 32:
    return 14;
  default:
    return -1;
  }
}

void aesBlock(unsigned char *state, unsigned char *roundkey, short keyLength, short action)
{
  short rounds = getRounds(keyLength);
  int i;

  addRoundKey(state, roundkey);
  if (action == 1)
  {
    for (i = 0; i < rounds; i++)
    {
      byteSub(state, action);
      shiftRow(state, action);
      if (i < rounds - 1)
      {
        mixColumn(state, action);
      }
      expandeKey(roundkey, i + 1);
      addRoundKey(state, roundkey);
    }
  }
  else
  {
    for (i = 0; i < rounds; i++)
    {
      shiftRow(state, action);
      byteSub(state, action);
      expandeKey(roundkey, i + 1);
      addRoundKey(state, roundkey);

      if (i < rounds - 1)
      {
        mixColumn(state, action);
      }
    }
  }
}

int aes(char *plaintext, short action, char *key)
{
  unsigned char roundkey[16];
  short keyLength = getKeyLength(key);

  if (keyLength == -1)
  {
    return -1;
  }

  // if descrypt, extract salt from plaintext
  unsigned char salt[16];
  if (action == -1)
  {
    for (int i = 16; i < 32; i++)
    {
      salt[i - 16] = plaintext[i];
    }
    removeBytes(plaintext, 16);
  }
  // derive key
  deriveKey(key, roundkey, keyLength, salt, action);

  int blocks = blocksCount(plaintext);
  unsigned char stateBlocks[blocks][16];

  // operation mode. TODO change to CBC mode
  toBlocks(plaintext, stateBlocks);

  for (int i = 0; i < blocks; i++)
  {
    aesBlock(stateBlocks[i], roundkey, keyLength, action);
  }

  // operation mode. TODO change to CBC mode
  toVector(stateBlocks, plaintext, blocks, salt, action);
  return 0;
}
int main()
{
  aes("texto", 1, "123456789012345678");
  return 0;
}
