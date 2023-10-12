#include <stdio.h>
#include "../to-blocks.h"
#include "test.utils.h"

#define TESTS 10
#define RANDOM_NUMBER_1_TO_ONE_MILLION() (1 + rand() % 1000000)
#define BLOCK_SIZE 16
void testToBlocks()
{
  printTestDescribe("testToBlocks");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    int plaintextSize = RANDOM_NUMBER_1_TO_ONE_MILLION();
    char plaintext[plaintextSize + 1];

    createPlaintext(plaintext, plaintextSize);
    printf("Teste com plaintext de tamanho %d\n", plaintext, plaintextSize);

    int plaintextBlocksCount = blocksCount(plaintext);
    unsigned char textBlocks[plaintextBlocksCount][BLOCK_SIZE];
    unsigned char receiveBytes[plaintextBlocksCount * 16];
    unsigned char expectBytes[plaintextBlocksCount * 16];
    toBlocks(plaintext, textBlocks);

    for (int i = 0; i < plaintextBlocksCount; i++)
    {
      memcpy(&receiveBytes[i * BLOCK_SIZE], textBlocks[i], BLOCK_SIZE);
      for (int j = 0; j < BLOCK_SIZE; j++)
      {
        // complete plaintext bytes with \0 for comparation
        int blockTextSize = (i == plaintextBlocksCount - 1) ? (plaintextSize - i * BLOCK_SIZE) : BLOCK_SIZE;

        expectBytes[i * BLOCK_SIZE + j] = (j <= blockTextSize) ? plaintext[i * BLOCK_SIZE + j] : ' ';
      }
    }

    eqVetor(receiveBytes, expectBytes, plaintextBlocksCount * BLOCK_SIZE);
    printf("\n");
  }
}

int main()
{

  testToBlocks();
  return 0;
}
