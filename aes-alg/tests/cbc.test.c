#include <stdio.h>
#include "../cbc.h"
#include "test.utils.h"
#include "../utils.h"

#define TESTS 10
#define RANDOM_NUMBER_1_TO_400() (1 + rand() % 400)

void testCBC()
{
  printTestDescribe("testCBC");
  printf("Same iv and same key of encrypt must reproduce the same plaintext result, results: \n\n");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    int plaintextSize = RANDOM_NUMBER_1_TO_400();
    char plaintext[plaintextSize];
    createPlaintext(plaintext, plaintextSize);
    printf("Teste com plaintext '%s', de tamanho %d\n", plaintext, plaintextSize);

    // Chave de 1 a 16
    unsigned char key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                             0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
                             0x0D, 0x0E, 0x0F, 0x10};

    unsigned char iv[16];

    int plaintextBlocksCount = blocksCount(plaintext);
    char cyphertext[plaintextBlocksCount * 16 + 1]; // blocksCount(plaintext) * 16 + 1(terminator "\0")
    unsigned char textBlocksEncryptResult[plaintextBlocksCount][16];
    unsigned char textBlocksDecryptResult[plaintextBlocksCount][16];

    cbc(plaintext, key, iv, 1, textBlocksEncryptResult);

    for (int i = 0; i < plaintextBlocksCount; i++)
    {
      for (int j = 0; j < 16; j++)
      {
        cyphertext[i * 16 + j] = (char)textBlocksEncryptResult[i][j];
      }
    }
    cyphertext[plaintextBlocksCount * 16] = '\0';

    cbc(cyphertext, key, iv, -1, textBlocksDecryptResult);

    unsigned char plaintextUC[plaintextSize];
    unsigned char cyphertextResult[plaintextBlocksCount * 16];

    for (int i = 0; i < plaintextBlocksCount; i++)
    {
      for (int j = 0; j < 16; j++)
      {

        cyphertextResult[i * 16 + j] = textBlocksDecryptResult[i][j];
        plaintextUC[i * 16 + j] = plaintext[i * 16 + j];
        if (countChar(plaintext) == i * 16 + j)
        {
          cyphertextResult[i * 16 + j] = '\0';
          break;
        }
      }
    }

    eqVetor(plaintextUC, cyphertextResult, plaintextSize);
  }
}

int main()
{

  testCBC();
  return 0;
}
