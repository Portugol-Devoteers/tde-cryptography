#include <stdio.h>
#include "../cbc.h"
#include "test.utils.h"
#include "../utils.h"
#include <string.h>
#include <stdlib.h>

#define TESTS 1
#define RANDOM_NUMBER_1_TO_400() (1 + rand() % 400)
#define BLOCK_SIZE 16
void testCBC()
{
  printTestDescribe("testCBC");
  printf("Same iv and same key of encrypt must reproduce the same plaintext result, results: \n\n");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    int plaintextSize = 18; // RANDOM_NUMBER_1_TO_400();
    char plaintext[plaintextSize + 1];
    createPlaintext(plaintext, plaintextSize);
    printf("Teste com plaintext '%s', de tamanho %d\n", plaintext, plaintextSize);

    // Chave de 1 a BLOCK_SIZE
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                     0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
                                     0x0D, 0x0E, 0x0F, 0x10};

    unsigned char iv[BLOCK_SIZE] = {0};

    int plaintextBlocksCount = blocksCount(plaintext);
    char ciphertext[plaintextBlocksCount * BLOCK_SIZE + 1]; // blocksCount(plaintext) * BLOCK_SIZE + 1(terminator "\0")
    unsigned char textBlocksEncryptResult[plaintextBlocksCount][BLOCK_SIZE];
    unsigned char textBlocksDecryptResult[plaintextBlocksCount][BLOCK_SIZE];

    cbc(plaintext, key, iv, 1, textBlocksEncryptResult);

    for (int i = 0; i < plaintextBlocksCount; i++)
    {
      memcpy(&ciphertext[i * BLOCK_SIZE], textBlocksEncryptResult[i], BLOCK_SIZE);
    }
    ciphertext[plaintextBlocksCount * BLOCK_SIZE] = '\0';

    cbc(ciphertext, key, iv, -1, textBlocksDecryptResult);

    unsigned char plaintextUC[plaintextSize];
    unsigned char ciphertextResult[plaintextBlocksCount * BLOCK_SIZE];

    for (int i = 0; i < plaintextBlocksCount; i++)
    {
      memcpy(&ciphertextResult[i * BLOCK_SIZE], textBlocksDecryptResult[i], BLOCK_SIZE);
      memcpy(&plaintextUC[i * BLOCK_SIZE], &plaintext[i * BLOCK_SIZE], BLOCK_SIZE);

      if (strlen(plaintext) == i * BLOCK_SIZE + BLOCK_SIZE)
      {
        ciphertextResult[i * BLOCK_SIZE + BLOCK_SIZE] = '\0';
        break;
      }
    }

    eqString(plaintextUC, ciphertextResult, plaintextSize);
  }
}

int main()
{

  testCBC();
  return 0;
}
