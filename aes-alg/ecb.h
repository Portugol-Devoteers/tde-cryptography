#ifndef ECB_H
#define ECB_H

#include "includes.h"

#define SALT_SIZE 16
#define DATA_SIZE_BYTES 4

/**
 * @brief Calcula o número de blocos de dados necessários para armazenar a quantidade de dados especificada, considerando uma operação de criptografia.
 *
 * Esta função calcula o número de blocos de dados necessários para acomodar a quantidade de dados especificada, levando em consideração uma operação de criptografia.
 *
 * @param[in] dataSize Tamanho dos dados a serem armazenados.
 * @param[in] operationType O tipo de operação (1 ou -1).
 * @return O número de blocos de dados necessários.
 */
int getBlockCount(uint32_t dataSize, short operationType);

/**
 * @brief Extrai o tamanho dos dados a partir dos primeiros 4 bytes de um vetor de dados.
 *
 * @param data Vetor de dados que contém os primeiros 4 bytes representando o tamanho.
 * @return O tamanho dos dados extraídos.
 */
uint32_t getDataSize(unsigned char *data);
/**
 * @brief Implementa o modo de operação ECB (Electronic Codebook) para criptografia ou descriptografia.
 *
 * @param data Um ponteiro para o vetor de dados a ser processado.
 * @param dataBlocks Uma matriz de blocos de dados resultantes.
 * @param salt Um ponteiro para o vetor que armazena o "salt" usado na derivação da chave.
 * @param dataSize Tamanho dos dados de entrada.
 * @param operationType O tipo de operação a ser executada (1 ou -1).
 * @return 0 se a operação for bem-sucedida; caso contrário, retorna um valor diferente.
 */
int ecb(unsigned char **data, unsigned char (*dataBlocks)[BLOCK_SIZE], unsigned char **salt, uint32_t dataSize, short operationType);

/**
 * @brief Implementa a operação inversa do modo de operação ECB (Electronic Codebook) para recuperar o vetor de texto original.
 *
 * @param dataBlocks Matriz de blocos de dados resultantes do processo de criptografia ou descriptografia.
 * @param dataSize Tamanho original dos dados de entrada.
 * @param dataVector Um ponteiro para o vetor de texto recuperado.
 * @param blocks O número de blocos de dados usados.
 * @param salt Um ponteiro para o "salt" usado na derivação da chave.
 * @param operationType O tipo de operação realizada (1 ou -1).
 */
void invEcb(unsigned char (*dataBlocks)[BLOCK_SIZE], uint32_t dataSize, unsigned char **dataVector, int blocks, unsigned char **salt, short operationType);

#endif /* ECB_H */
