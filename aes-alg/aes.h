#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core.h"
#include "derive-key.h"
#include "utils.h"
#include "operation-mode.h"
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

  if (rounds == -1)
  {
    printf("Erro ao obter o número de rounds.\n");
    return;
  }

  if (action == 1)
  {
    addRoundKey(state, roundkey);
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

    addRoundKey(state, roundkeyRound[rounds]);

    for (i = rounds - 1; i >= 0; i--)
    {
      shiftRow(state, action);
      byteSub(state, action);
      addRoundKey(state, roundkeyRound[i]);

      if (i > 0)
      {
        mixColumn(state, action);
      }
    }
  }
}

int aes(unsigned char **text, short action, char *key)
{
  unsigned char roundkey[16];
  short keyLength = getKeyLength(key);
  uint32_t textSize = getTextSize(*text);
  int blocks = blocksCount(textSize);
  unsigned char stateBlocks[blocks][16];
  unsigned char *salt = (unsigned char *)malloc(16 * sizeof(unsigned char));

  if (keyLength == -1)
  {
    return -1;
  }

  // operation mode.
  ecb(text, stateBlocks, &salt, textSize, action);

  // derive key
  deriveKey(key, roundkey, &keyLength, &salt, action);

  for (int i = 0; i < blocks; i++)
  {
    aesBlock(stateBlocks[i], roundkey, keyLength, action);
  }

  // operation mode.
  invEcb(stateBlocks, textSize, text, blocks, &salt, action);

  free(salt);
  return 0;
}
