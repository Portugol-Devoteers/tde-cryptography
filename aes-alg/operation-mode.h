#include <stdio.h>
#include <string.h>
#include <math.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16
#define SALT_SIZE 16
#define TEXT_SIZE_BYTES 4

extern int blocksCount(uint32_t textSize)
{
  return (int)ceil((double)textSize / BLOCK_SIZE);
}

int getTextSize(unsigned char *textInBytes)
{
  // extract textInBytes size from the first TEXT_SIZE_BYTES (4) bytes
  unsigned char textSizeBytes[TEXT_SIZE_BYTES];

  for (int i = 0; i < TEXT_SIZE_BYTES; i++)
  {
    textSizeBytes[i] = textInBytes[i];
  }

  return bytesToUInt(textSizeBytes);
}

int ecb(unsigned char **textInBytes, unsigned char (*textBlocks)[BLOCK_SIZE], unsigned char **deriveKeySalt, uint32_t textSize, short action)
{
  short bytesToRemove = TEXT_SIZE_BYTES;

  if (action == -1)
  {
    memcpy((*deriveKeySalt), (*textInBytes) + TEXT_SIZE_BYTES, SALT_SIZE);
    bytesToRemove += SALT_SIZE;
  }
  removeBytes(textInBytes, textSize, bytesToRemove);

  int blocks = blocksCount(textSize);

  // create a newBlock when the textInBytes size is a multiple of BLOCK_SIZE and action is 1 (encrypt)
  if (action == 1 && textSize % BLOCK_SIZE == 0)
  {
    blocks++;
  }

  for (int blockIndex = 0; blockIndex < blocks; blockIndex++)
  {
    // count the number of bytes in the block, if the block is the last, the number of bytes is the remainder of the division
    // Ex: textSize = 32, BLOCK_SIZE = 16, blocks = 3, blockIndex = 2, blockTextSize = 32 - 2 * 16 = 0
    // Ex: textSize = 33, BLOCK_SIZE = 16, blocks = 3, blockIndex = 2, blockTextSize = 33 - 2 * 16 = 1
    // Ex: textSize = 6, BLOCK_SIZE = 16, blocks = 1, blockIndex = 0, blockTextSize = 6 - 0 * 16 = 6
    // ex: textSize = 807988, BLOCK_SIZE = 16, blocks = 50500, blockIndex = 50499, blockTextSize = 807988 - 50499 * 16 = 4
    int blockTextSize = (blockIndex == blocks - 1) ? (textSize - blockIndex * BLOCK_SIZE) : BLOCK_SIZE;

    // create a padding byte, if the block is the last, the padding byte is the number of bytes to complete the block
    unsigned char paddingByte = (blockTextSize < BLOCK_SIZE) ? (BLOCK_SIZE - blockTextSize) : BLOCK_SIZE;

    for (int byteIndex = 0; byteIndex < BLOCK_SIZE; byteIndex++)
    {
      // ex: textSize: 24, blockTextSize: 16, blockIndex = 0, byteIndex = 0, textBlocks[0][0] = textInBytes[0]
      // ex: textSize: 32, blockTextSize: 0, blockIndex = 2, byteIndex = 0, textBlocks[2][1] = paddingByte
      textBlocks[blockIndex][byteIndex] = (byteIndex < blockTextSize) ? (*textInBytes)[blockIndex * BLOCK_SIZE + byteIndex] : paddingByte;
    }
  }

  return 0;
}
/**
 * Função do modo de operaçao que desfaz os blocos e passa para o vetor de texto. Quando action -1 (descriptografar), remove os bytes de preenchimento
 */
void invEcb(unsigned char (*textBlocks)[BLOCK_SIZE], uint32_t textSize, unsigned char **textVector, int blocks, unsigned char **salt, short action)
{
  int vectorSize = blocks * BLOCK_SIZE + TEXT_SIZE_BYTES;
  unsigned char textSizeBytes[4];
  short initMessage = TEXT_SIZE_BYTES;
  unsigned char lastByte = textBlocks[blocks - 1][BLOCK_SIZE - 1];

  // Coloca o tamanho do texto e o salt no inicio do vetor se for action 1 (criptografar)
  if (action == 1)
  {
    vectorSize += SALT_SIZE;
    initMessage += SALT_SIZE;
    textSize = textSize + (BLOCK_SIZE - textSize % BLOCK_SIZE);
  }
  else
  {
    // Quando action -1 (descriptografar), remove os bytes de preenchimento
    vectorSize -= lastByte;
    textSize -= lastByte;
  }

  reallocMemory(textVector, vectorSize);

  uintToBytes(textSize, textSizeBytes);

  for (int textVIndex = 0; textVIndex < vectorSize; textVIndex++)
  {
    if (textVIndex < TEXT_SIZE_BYTES)
    {
      (*textVector)[textVIndex] = textSizeBytes[textVIndex];
    }
    else if (textVIndex < initMessage) // if action == 1, move salt to the first BLOCK_SIZE bytes
    {
      (*textVector)[textVIndex] = (*salt)[textVIndex - TEXT_SIZE_BYTES];
    }
    else
    {
      short blockIndex = (textVIndex - initMessage) / BLOCK_SIZE;
      short byteIndex = (textVIndex - initMessage) % BLOCK_SIZE;

      (*textVector)[textVIndex] = textBlocks[blockIndex][byteIndex];
    }
  }
}