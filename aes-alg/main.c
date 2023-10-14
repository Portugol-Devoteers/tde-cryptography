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
  unsigned char localState[16];

  for (i = 0; i < 16; i++)
  {
    localState[i] = state[i];
  }

  if (action == 1)
  {
    addRoundKey(localState, roundkey);
    for (i = 0; i < rounds; i++)
    {
      byteSub(localState, action);
      shiftRow(localState, action);
      if (i < rounds - 1)
      {
        mixColumn(localState, action);
      }
      expandeKey(roundkey, i + 1);
      addRoundKey(localState, roundkey);
    }
  }
  else
  {
    unsigned char roundkeyRound[rounds + 1][16];

    // Save round 0 key
    for (i = 0; i < 16; i++)
    {
      roundkeyRound[0][i] = roundkey[i];
    }

    // get all keys
    for (i = 1; i <= rounds; i++)
    {
      expandeKey(roundkey, i);
      for (int j = 0; j < 16; j++)
      {
        roundkeyRound[i][j] = roundkey[j];
      }
    }

    addRoundKey(localState, roundkeyRound[rounds]);

    for (i = rounds - 1; i >= 0; i--)
    {
      shiftRow(localState, action);
      byteSub(localState, action);
      addRoundKey(localState, roundkeyRound[i]);

      if (i > 0)
      {
        mixColumn(localState, action);
      }
    }
  }

  for (i = 0; i < 16; i++)
  {
    state[i] = localState[i];
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
  // if (action == -1)
  // {
  //   for (int i = 16; i < 32; i++)
  //   {
  //     salt[i - 16] = plaintext[i];
  //   }
  //   removeBytes(plaintext, 16);
  // }
  // // derive key
  // deriveKey(key, roundkey, keyLength, salt, action);
  for (int i = 0; i < 16; i++)
  {
    roundkey[i] = key[i];
  }

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
  char texto[17] = "ABCDEFGH";
  char key[] = "1234567890123456";
  // print input in bytes
  for (int i = 0; i < 16; i++)
  {
    printf("%02X ", (unsigned char)texto[i]);
  }
  printf("\n");
  aes(texto, 1, key);

  // print bytes with a space between
  for (int i = 0; i < 16; i++)
  {
    printf("%02X ", (unsigned char)texto[i]);
  }
  printf("\n");

  aes(texto, -1, key);

  // print bytes with a space between
  for (int i = 0; i < 16; i++)
  {
    printf("%02X ", (unsigned char)texto[i]);
  }
  printf("\n");

  return 0;
}
