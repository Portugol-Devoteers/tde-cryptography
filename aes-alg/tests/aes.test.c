#include <stdio.h>
#include "../aes.h"
#include "test.utils.h"
#include "../utils.h"

#define MAX_TEXT_SIZE 100000
#define MIN_TEXT_SIZE 1
#define TESTS 1
#define RANDOM_NUMBER() (MIN_TEXT_SIZE + rand() % MAX_TEXT_SIZE)
#define RANDOM_KEY_SIZE() (1 + rand() % 16)
#define BLOCK_SIZE 16

void testAES()
{
  printTestDescribe("testAES");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    uint32_t dataSize = RANDOM_NUMBER();
    char plaintext[dataSize + 1];
    loren(plaintext, dataSize);

    printf("Teste com plaintext de tamanho %d\n", dataSize);

    // Data size + 4 bytes to store the data size
    unsigned char *data = (unsigned char *)malloc((dataSize + 4) * sizeof(unsigned char));
    unsigned char originalText[dataSize + 4];

    unsigned char dataSizeInBytes[4];
    uintToBytes(dataSize, dataSizeInBytes);

    // test data size value
    uint32_t bytesToint = bytesToUInt(dataSizeInBytes);
    if (bytesToint != dataSize)
    {
      printf("Erro: Não foi possível converter o tamanho dos dados para bytes.\n");
      return;
    }

    for (int i = 0; i < dataSize + 4; i++)
    {
      if (i < 4)
      {
        originalText[i] = dataSizeInBytes[i];
        data[i] = dataSizeInBytes[i];
      }
      else
      {
        originalText[i] = plaintext[i - 4];
        data[i] = plaintext[i - 4];
      }
    }
    int keySize = RANDOM_KEY_SIZE();
    char key[keySize + 1];
    loren(key, keySize);

    aes(&data, Encrypt, key);

    printf("\n");
    aes(&data, Decrypt, key);

    eqVetor(data, originalText, dataSize + 4);
    printf("\n");
  }
}

int main()
{
  testAES();
  return 0;
}
