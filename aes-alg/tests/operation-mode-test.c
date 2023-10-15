#include <stdio.h>
#include "../ecb.h"
#include "test-utils.h"

// TODO update this test to use the new ecb.h

#define TESTS 10
#define RANDOM_NUMBER_1_TO_ONE_MILLION() (1 + rand() % 1000000)
#define BLOCK_SIZE 16
void testToBlocks()
{
  printTestDescribe("testToBlocks");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    int plaindataSize = RANDOM_NUMBER_1_TO_ONE_MILLION();
    char plaintext[plaindataSize + 1];

    loren(plaintext, plaindataSize);
    printf("Teste com plaintext de tamanho %d\n", plaindataSize);

    int plaindatagetBlockCount = getBlockCount(plaintext);
    unsigned char dataBlocks[plaindatagetBlockCount][BLOCK_SIZE];
    unsigned char receiveBytes[plaindatagetBlockCount * 16];
    unsigned char expectBytes[plaindatagetBlockCount * 16];
    ecb(plaintext, dataBlocks);

    for (int i = 0; i < plaindatagetBlockCount; i++)
    {
      memcpy(&receiveBytes[i * BLOCK_SIZE], dataBlocks[i], BLOCK_SIZE);
      for (int j = 0; j < BLOCK_SIZE; j++)
      {
        // complete plaintext bytes with \0 for comparation
        int blockdataSize = (i == plaindatagetBlockCount - 1) ? (plaindataSize - i * BLOCK_SIZE) : BLOCK_SIZE;

        expectBytes[i * BLOCK_SIZE + j] = (j <= blockdataSize) ? plaintext[i * BLOCK_SIZE + j] : '\0';
      }
    }

    eqVetor(receiveBytes, expectBytes, plaindatagetBlockCount * BLOCK_SIZE);
    printf("\n");
  }
}

int main()
{

  testToBlocks();
  return 0;
}
