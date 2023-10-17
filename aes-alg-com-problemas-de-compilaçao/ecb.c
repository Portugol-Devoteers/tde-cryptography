
#include "ecb.h"
#include "includes.h"

int getBlockCount(uint32_t dataSize, short operationType)
{
  // Calcula o número de blocos arredondando para cima usando ceil
  int blocks = (int)ceil((double)dataSize / BLOCK_SIZE);

  // Se a operação for de criptografia e o tamanho dos dados for múltiplo do tamanho do bloco, um novo bloco é adicionado
  if (operationType == 1 && dataSize % BLOCK_SIZE == 0)
  {
    blocks++;
  }
  return blocks;
}

uint32_t getDataSize(unsigned char *data)
{
  // Extrai os 4 bytes iniciais que representam o tamanho
  unsigned char dataSizeInBytes[DATA_SIZE_BYTES];

  for (int i = 0; i < DATA_SIZE_BYTES; i++)
  {
    dataSizeInBytes[i] = data[i];
  }

  return bytesToUInt(dataSizeInBytes);
}

int ecb(unsigned char **data, unsigned char (*dataBlocks)[BLOCK_SIZE], unsigned char **salt, uint32_t dataSize, short operationType)
{
  // Calcula quantos bytes precisam ser removidos dos dados, dependendo da operação
  short bytesToRemove = DATA_SIZE_BYTES;

  if (operationType == -1)
  {
    // Se estiver descriptografando, o "salt" é copiado e removido dos dados
    memcpy((*salt), (*data) + DATA_SIZE_BYTES, SALT_SIZE);
    bytesToRemove += SALT_SIZE;
  }
  removeBytes(data, dataSize, bytesToRemove);

  // Calcula o número de blocos necessários com base no tamanho dos dados
  int blocks = getBlockCount(dataSize, operationType);

  // Divide os dados em blocos, adicionando preenchimento, conforme necessário
  for (int blockIndex = 0; blockIndex < blocks; blockIndex++)
  {
    // Calcula o tamanho do bloco atual
    int blockdataSize = (blockIndex == blocks - 1) ? (dataSize - blockIndex * BLOCK_SIZE) : BLOCK_SIZE;

    // Calcula o byte de preenchimento para o bloco atual
    unsigned char paddingByte = (blockdataSize < BLOCK_SIZE) ? (BLOCK_SIZE - blockdataSize) : BLOCK_SIZE;

    for (int byteIndex = 0; byteIndex < BLOCK_SIZE; byteIndex++)
    {
      // Copia os bytes dos dados para o bloco, adicionando preenchimento
      dataBlocks[blockIndex][byteIndex] = (byteIndex < blockdataSize) ? (*data)[blockIndex * BLOCK_SIZE + byteIndex] : paddingByte;
    }
  }

  return 0;
}

void invEcb(unsigned char (*dataBlocks)[BLOCK_SIZE], uint32_t dataSize, unsigned char **dataVector, int blocks, unsigned char **salt, short operationType)
{
  // Calcula o tamanho final do vetor de dados com base no número de blocos
  int vectorSize = blocks * BLOCK_SIZE + DATA_SIZE_BYTES;
  unsigned char dataSizeInBytes[4];
  short initdata = DATA_SIZE_BYTES;
  unsigned char lastByte = dataBlocks[blocks - 1][BLOCK_SIZE - 1];

  // Adiciona os 4 bytes que representam quantos bytes compõem os dados e o "salt" no início do vetor se for uma operação de criptografia
  if (operationType == 1)
  {
    vectorSize += SALT_SIZE;
    initdata += SALT_SIZE;
    dataSize = dataSize + (BLOCK_SIZE - dataSize % BLOCK_SIZE);
  }
  else
  {
    // Remove os bytes de preenchimento quando descriptografando
    vectorSize -= lastByte;
    dataSize -= lastByte;
  }

  reallocMemory(dataVector, vectorSize);

  // Converte a quantidade de bytes dos dados em 4 bytes
  uintToBytes(dataSize, dataSizeInBytes);

  for (int textVIndex = 0; textVIndex < vectorSize; textVIndex++)
  {
    if (textVIndex < DATA_SIZE_BYTES)
    {
      // Copia os 4 bytes que representam quantos bytes compõem os dados no início do vetor
      (*dataVector)[textVIndex] = dataSizeInBytes[textVIndex];
    }
    else if (textVIndex < initdata)
    {
      // Se a operação for de criptografia, move o "salt" para os primeiros bytes do vetor depois dos 4 iniciais que representam o tamanho dos dados
      (*dataVector)[textVIndex] = (*salt)[textVIndex - DATA_SIZE_BYTES];
    }
    else
    {
      // Copia os bytes dos blocos de dados no vetor de data
      short blockIndex = (textVIndex - initdata) / BLOCK_SIZE;
      short byteIndex = (textVIndex - initdata) % BLOCK_SIZE;

      (*dataVector)[textVIndex] = dataBlocks[blockIndex][byteIndex];
    }
  }
}
