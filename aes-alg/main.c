#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core.h"
#include "derive-key.h"
#include "utils.h"
#include "cbc.h"

int aes(char *plaintext, short action, char *key)
{
  // 1. Preparação do texto, o texto é convertido para blocos de texto de 16 bytes.
  // 2. Preparaçao da chave,  é feita a expançao, resultando em um vetor de n chaves de 16 bytes.
  // 3. Cada bloco de texto é cifrado com as chaves expandida.

  short keyLength = getKeyLength(key);
  if (keyLength == -1)
  {
    return -1;
  }

  // if descrypt, extract iv from 0 to 16 bytes and salt from 16 to 32 bytes from plaintext, and remove from plaintext

  unsigned char salt[16];
  unsigned char iv[16];
  if (action == -1)
  {
    for (int i = 0; i < 16; i++)
    {
      iv[i] = plaintext[i];
    }
    for (int i = 16; i < 32; i++)
    {
      salt[i - 16] = plaintext[i];
    }
    removeBytes(plaintext, 32);
  }

  deriveKey(key, keyLength, salt, -1);

  // Transforma a key em um vetor de 16 bytes
  unsigned char keyBytes[16];
  for (int i = 0; i < 16; i++)
  {
    keyBytes[i] = key[i];
  }

  unsigned char stateBlocks[blocksCount(plaintext)][16];

  cbc(plaintext, keyBytes, iv, action, stateBlocks);

  // expanded key (n keys of 16 bytes)

  // int i;
  // for (i = 0; i < 16; i++) {
  //   addRoundKey(plaintext, key);
  //   byteSub(state, action);
  //   shiftRow(state, action);
  //   if (i < 9) {
  //     mixColumn(state, action);
  //   }
  // }
  // addRoundKey(plaintext, key);
  return 0;
}
int main()
{
  /*
    1. Preparação do texto, o texto é convertido para blocos de texto de 16 bytes.
    2. Preparaçao da chave, é feita a expançao, resultando em um vetor de n chaves de 16 bytes.
    3. Cada bloco de texto é cifrado com as chaves expandida.
  */

  aes("texto", 1, "123456789012345678");
  return 0;
}
