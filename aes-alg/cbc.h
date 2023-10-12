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

int cbc(char *text, unsigned char *keyBytes, unsigned char *iv, short action, unsigned char (*textBlocks)[BLOCK_SIZE])
{
  int textSize = strlen(text);

  // create a new block in bytes

  unsigned char textInBytes[textSize];
  for (int i = 0; i < textSize; i++)
  {
    textInBytes[i] = (unsigned char)text[i];
  }

  int blocks = blocksCount(text);

  // Atribui o iv para o ivCopy, criando bytes aleatorios caso seja a criptografia, se nao copia o iv
  unsigned char xorVectorAux[BLOCK_SIZE];
  if (action == 1)
  {
    RAND_bytes(iv, BLOCK_SIZE * 2);
  }
  // inicia o vetor auxiliar que será usado nas operaçoes de xor
  for (int i = 0; i < BLOCK_SIZE; i++)
  {
    xorVectorAux[i] = iv[i];
  }

  for (int i = 0; i < blocks; i++)
  {
    int blockTextSize = (i == blocks - 1) ? (textSize - i * BLOCK_SIZE) : BLOCK_SIZE;

    for (int j = 0; j < BLOCK_SIZE; j++)
    {
      unsigned char charBlockAnterior = (i == 0) ? iv[j] : textInBytes[(i - 1) * BLOCK_SIZE + j];
      unsigned char charBlockAtual = (j < blockTextSize) ? textInBytes[i * BLOCK_SIZE + j] : '\0';
      unsigned char charKey = keyBytes[j];
      unsigned char charXor = (action == 1) ? (charBlockAtual ^ charKey ^ xorVectorAux[j]) : (charBlockAtual ^ charKey ^ charBlockAnterior);
      textBlocks[i][j] = charXor;
      xorVectorAux[j] = charXor; // Update xorVectorAux for the next iteration
    }
  }

  return 0;
}