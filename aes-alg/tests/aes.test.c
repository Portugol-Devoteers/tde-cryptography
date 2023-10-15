#include <stdio.h>
#include "../aes.h"
#include "test.utils.h"
#include "../utils.h"

#define MAX_TEXT_SIZE 10000
#define TESTS 10
#define RANDOM_NUMBER() (1 + rand() % MAX_TEXT_SIZE)
#define RANDOM_KEY_SIZE() (1 + rand() % 16)
#define BLOCK_SIZE 16

void testAES()
{
  printTestDescribe("testAES");

  for (int testCase = 0; testCase < TESTS; testCase++)
  {
    uint32_t textSize = RANDOM_NUMBER();
    char plaintext[textSize + 1];
    createPlaintext(plaintext, textSize);
    printf("Teste com plaintext de tamanho %d\n", textSize);

    // Text size + 4 bytes to store the text size
    unsigned char *state = (unsigned char *)malloc((textSize + 4) * sizeof(unsigned char));
    unsigned char originalText[textSize + 4];

    unsigned char textSizeBytes[4];
    uintToBytes(textSize, textSizeBytes);

    // test text size value
    uint32_t bytesToint = bytesToUInt(textSizeBytes);
    if (bytesToint != textSize)
    {
      printf("Erro ao converter o tamanho do texto para bytes.\n");
      return;
    }

    for (int i = 0; i < textSize + 4; i++)
    {
      if (i < 4)
      {
        originalText[i] = textSizeBytes[i];
        state[i] = textSizeBytes[i];
      }
      else
      {
        originalText[i] = plaintext[i - 4];
        state[i] = plaintext[i - 4];
      }
    }
    int keySize = RANDOM_KEY_SIZE();
    char key[keySize + 1];
    createPlaintext(key, keySize);

    aes(&state, 1, key);

    printf("\n");
    aes(&state, -1, key);

    eqVetor(state, originalText, textSize + 4);
    printf("\n");
  }
}

int main()
{
  testAES();
  return 0;
}
