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
  int count = countChar(plaintext);
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

int cbc(char *plaintext, unsigned char *keyBytes, unsigned char *iv, short action, unsigned char (*textBlocks)[16])
{
  // Atribui o iv para o ivCopy, criando bytes aleatorios caso seja a criptografia, se nao copia o iv
  unsigned char ivCopy[16];
  if (action == 1)
  {
    RAND_bytes(ivCopy, sizeof(ivCopy));
  }
  else
  {
    for (int i = 0; i < 16; i++)
    {
      ivCopy[i] = iv[i];
    }
  }

  // inicia o vetor auxiliar que será usado nas operaçoes de xor na criptografia
  unsigned char xorVetorAux[16];
  for (int i = 0; i < 16; i++)
  {
    xorVetorAux[i] = ivCopy[i];
  }

  // inicia o vetor auxiliar que será usado nas operaçoes de xor na descriptografia
  unsigned char blockCryptedAux[16];
  for (int i = 0; i < 16; i++)
  {
    blockCryptedAux[i] = ivCopy[i];
  }

  for (int i = 0; i < blocksCount(plaintext); i++)
  {
    unsigned char block[16];

    // conta quantos caracters tem no plaintext que está sendo verificado atualmente usando countChar
    char plaintextBlock[16];
    for (int j = 0; j < 16; j++)
    {
      plaintextBlock[j] = plaintext[i * 16 + j];
    }
    int plaintextBlockCharsCount = countChar(plaintextBlock);

    for (int j = 0; j < 16; j++)
    {
      block[j] = plaintextBlockCharsCount > j ? plaintext[i * 16 + j] : '0';
    }

    if (action == 1)
    {
      for (int j = 0; j < 16; j++)
      {
        // faz xor com o iv na primeira vez e depois com o resultado do bloco anterior
        // faz xor com a chave secreta
        block[j] = block[j] ^ xorVetorAux[j] ^ keyBytes[j];
        // copia o resultado para o vetor auxiliar para o proximo ser usado no xor do proximo bloco
        xorVetorAux[j] = block[j];
      }
    }
    else
    {
      for (int j = 0; j < 16; j++)
      {
        // faz xor com a chave secreta
        // faz xor com o iv na primeira vez e depois com o resultado do bloco anterior
        block[j] = block[j] ^ keyBytes[j] ^ blockCryptedAux[j];
        // copia o resultado para o vetor auxiliar para o proximo ser usado no xor do proximo bloco
        blockCryptedAux[j] = block[j];
      }
    }

    // salva o bloco no vetor de blocos
    for (int j = 0; j < 16; j++)
    {
      textBlocks[i][j] = block[j];
    }
  }

  // copia o ivCopy para o iv
  for (int i = 0; i < 16; i++)
  {
    iv[i] = ivCopy[i];
  }
  return 0;
}