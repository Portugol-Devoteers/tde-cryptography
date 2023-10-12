#include <stdio.h>
#include <string.h>
#include <math.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16

extern int blocksCount(char *text)
{
  int count = strlen(text);
  return (int)ceil((double)count / BLOCK_SIZE);
}

int toBlocks(char *text, unsigned char (*textBlocks)[BLOCK_SIZE])
{
  int textSize = strlen(text);

  // create a new block in bytes

  unsigned char textInBytes[textSize];
  for (int i = 0; i < textSize; i++)
  {
    textInBytes[i] = (unsigned char)text[i];
  }

  int blocks = blocksCount(text);

  for (int i = 0; i < blocks; i++)
  {
    int blockTextSize = (i == blocks - 1) ? (textSize - i * BLOCK_SIZE) : BLOCK_SIZE;

    for (int j = 0; j < BLOCK_SIZE; j++)
    {
      textBlocks[i][j] = (j < blockTextSize) ? textInBytes[i * BLOCK_SIZE + j] : ' ';
    }
  }

  return 0;
}

void toVector(unsigned char (*textBlocks)[BLOCK_SIZE], unsigned char *textVector, int blocks, unsigned char *salt, short action)
{
  int vectorSize = blocks * BLOCK_SIZE;

  // if (action == 1) move salt to the first 16 bytes
  if (action == 1)
  {
    vectorSize += 16;
  }
  for (int i = 0; i < vectorSize; i++)
  {
    if (action == 1 && i < 16)
    {
      textVector[i] = salt[i];
      continue;
    }
    textVector[i] = textBlocks[i / BLOCK_SIZE][i % BLOCK_SIZE];
  }
}