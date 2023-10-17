#include <stdio.h>
#include "../derive-key.h"
#include "test.utils.h"
#include "../utils.h"

#define TESTS 6

void testDeriveKey()
{
  printTestDescribe("testDeriveKey");
  char keysForTest[TESTS][32] = {
      "123456789",                       // 9
      "1234567890123456",                // 16
      "12345678901234561234",            // 20
      "123456789012345612345678",        // 24
      "12345678901234561234567890",      // 28
      "1234567890123456789012345678901", // 32
  };

  printf("Same salt and same key of encrypt must reproduce the same derivated key, results: \n\n");

  for (int i = 0; i < TESTS; i++)
  {
    printf("Teste com chave %s de tamanho %d\n", keysForTest[i], getKeyLength(keysForTest[i]));
    unsigned char salt[16];

    short keyLength = getKeyLength(keysForTest[i]);

    if (keyLength == -1)
    {
      return;
    }

    unsigned char keySize = getNearestKeySize(keyLength);
    unsigned char keyEncryptResult[keySize];
    unsigned char keyDecryptResult[keySize];

    deriveKey(keysForTest[i], keyEncryptResult, &keyLength, salt, Encrypt);

    // trocar 1 caracter do salt muda o resultado, por isso é seguro.
    // salt[0] = '@';

    deriveKey(keysForTest[i], keyDecryptResult, &keyLength, salt, Decrypt);

    eqVetor(keyEncryptResult, keyDecryptResult, keySize);
    printf("\n");
  }
  printf("========================================\n\n\n");
}

int main()
{

  testDeriveKey();
  return 0;
}
