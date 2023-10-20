#include <stdio.h>
#include <string.h>
#include <math.h>

#define BLOCK_SIZE 16
#define DATA_SIZE_BYTES 4

/**
 * @brief Calcula o número de blocos de dados necessários para armazenar a quantidade de dados especificada, considerando uma operação de criptografia.
 *
 * Esta função calcula o número de blocos de dados necessários para acomodar a quantidade de dados especificada, levando em consideração uma operação de criptografia.
 *
 * @param[in] dataSize Tamanho dos dados a serem armazenados.
 * @param[in] operationType O tipo de operação (Encrypt ou Decrypt).
 * @return O número de blocos de dados necessários.
 */
int getBlockCount(uint32_t dataSize, enum OperationType operationType)
{
  // Calcula o número de blocos arredondando para cima usando ceil
  int blocks = (int)ceil((double)dataSize / BLOCK_SIZE);

  // Se a operação for de criptografia e o tamanho dos dados for múltiplo do tamanho do bloco, um novo bloco é adicionado
  if (operationType == Encrypt && dataSize % BLOCK_SIZE == 0)
  {
    blocks++;
  }
  return blocks;
}

/**
 * @brief Extrai o tamanho dos dados a partir dos primeiros 4 bytes de um vetor de dados.
 *
 * @param data Vetor de dados que contém os primeiros 4 bytes representando o tamanho.
 * @return O tamanho dos dados extraídos.
 */
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

/**
 * @brief Implementa o modo de operação ECB (Electronic Codebook) para criptografia ou descriptografia.
 *
 * @param data Um ponteiro para o vetor de dados a ser processado.
 * @param dataBlocks Uma matriz de blocos de dados resultantes.
 * @param dataSize Tamanho dos dados de entrada.
 * @param operationType O tipo de operação a ser executada (Encrypt ou Decrypt).
 * @return 0 se a operação for bem-sucedida; caso contrário, retorna um valor diferente.
 */
int ecb(unsigned char **data, unsigned char (*dataBlocks)[BLOCK_SIZE], uint32_t dataSize, enum OperationType operationType)
{
  // remove os 4 bytes iniciais que representam o tamanho dos dados
  removeBytes(data, dataSize, DATA_SIZE_BYTES);

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

/**
 * @brief Implementa a operação inversa do modo de operação ECB (Electronic Codebook) para recuperar o vetor de texto original.
 *
 * @param dataBlocks Matriz de blocos de dados resultantes do processo de criptografia ou descriptografia.
 * @param dataSize Tamanho original dos dados de entrada.
 * @param dataVector Um ponteiro para o vetor de texto recuperado.
 * @param blocks O número de blocos de dados usados.
 * @param operationType O tipo de operação realizada (Encrypt ou Decrypt).
 */
void invEcb(unsigned char (*dataBlocks)[BLOCK_SIZE], uint32_t dataSize, unsigned char **dataVector, int blocks, enum OperationType operationType)
{
  // Calcula o tamanho final do vetor de dados com base no número de blocos
  int vectorSize = blocks * BLOCK_SIZE + DATA_SIZE_BYTES;
  unsigned char dataSizeInBytes[4];
  short initdata = DATA_SIZE_BYTES;
  unsigned char lastByte = dataBlocks[blocks - 1][BLOCK_SIZE - 1];

  // Adiciona os 4 bytes que representam quantos bytes compõem os dados no início do vetor se for uma operação de criptografia
  if (operationType == Encrypt)
  {
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
    else
    {
      // Copia os bytes dos blocos de dados no vetor de data
      short blockIndex = (textVIndex - initdata) / BLOCK_SIZE;
      short byteIndex = (textVIndex - initdata) % BLOCK_SIZE;

      (*dataVector)[textVIndex] = dataBlocks[blockIndex][byteIndex];
    }
  }
}