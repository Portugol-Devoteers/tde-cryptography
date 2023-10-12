#include <stdio.h>
#include <string.h>
#include <math.h>
#include <openssl/rand.h>

int countChar(char *plaintext)
{
  int count = 0;
  while (*plaintext != '\0')
  {
    count++;
    plaintext++;
  }

  return count;
}
extern int blocksCount(char *plaintext)
{
  int count = strlen(plaintext);
  return ceil((double)count / 16);
}

void completeBlockWithZeros(char *block)
{
  int count = 0;
  while (*block != '\0')
  {
    count++;
    block++;
  }

  for (int i = count; i < 16; i++)
  {
    block[i] = 0;
  }
}

int cbc(char *text, unsigned char *keyBytes, unsigned char *iv, short action, unsigned char (*textBlocks)[16])
{
  int textSize = countChar(text);

  // create a new block in bytes

  unsigned char textInBytes[textSize];
  for (int i = 0; i < textSize; i++)
  {
    textInBytes[i] = text[i];
  }

  int blocks = (int)ceil((double)textSize / 16);

  // Atribui o iv para o ivCopy, criando bytes aleatorios caso seja a criptografia, se nao copia o iv
  unsigned char xorVetorAux[16];
  if (action == 1)
  {
    RAND_bytes(iv, sizeof(iv));

    // inicia o vetor auxiliar que será usado nas operaçoes de xor
    for (int i = 0; i < 16; i++)
    {
      xorVetorAux[i] = iv[i];
    }
  }
  else
  {
    for (int i = 0; i < 16; i++)
    {
      xorVetorAux[i] = iv[i];
    }
  }

  for (int i = 0; i < blocks; i++)
  {
    int blockTextSize = (i == blocks - 1) ? (textSize - i * 16) : 16;

    if (action == 1)
    {
      for (int j = 0; j < 16; j++)
      {
        unsigned char c = blockTextSize > j ? textInBytes[i * 16 + j] : '\0';
        // faz xor com o iv na primeira vez e depois com o resultado do bloco anterior
        // faz xor com a chave secreta
        // copia o resultado para o vetor auxiliar para o proximo ser usado no xor do proximo bloco
        xorVetorAux[j] = c ^ xorVetorAux[j] ^ keyBytes[j];
        textBlocks[i][j] = xorVetorAux[j];
      }
    }
    else
    {
      for (int j = 0; j < 16; j++)
      {
        // faz xor com a chave secreta
        // faz xor com o iv na primeira vez e depois com o bloco criptografado anterior
        // copia o resultado direto no vetor de blocos para evitar loop desnecessario na descriptografia
        unsigned char charBlockAnterior = i == 0 ? iv[j] : textInBytes[(i - 1) * 16 + j];
        unsigned char charBlockAtual = textInBytes[i * 16 + j];
        unsigned char charKey = keyBytes[j];
        unsigned char charXor = charBlockAtual ^ charKey ^ charBlockAnterior;
        textBlocks[i][j] = charXor;
      }
    }
  }

  return 0;
}