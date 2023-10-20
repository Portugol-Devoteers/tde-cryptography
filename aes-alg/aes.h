#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core.h"
#include "derive-key.h"
#include "utils.h"
#include "operation-mode.h"
#include "expand-key.h"

/**
 * @file aes.h
 * @brief Arquivo de cabeçalho para funções relacionadas ao algoritmo AES.
 */

/**
 * @brief Realiza uma única operação AES em um bloco de dados.
 *
 * Esta função executa uma única operação AES (criptografia ou descriptografia) em um
 * bloco de dados representado pelo estado `state`. A operação é determinada pelo tipo
 * de operação especificado em `operationType`. A chave de rodada `roundkey` é usada
 * para a operação.
 *
 * @param[in,out] state O estado do bloco de dados a ser processado.
 * @param[in] roundkey A chave de rodada a ser usada na operação. Deve ter 16 bytes. Sempre é a chave de rodada 0.
 * @param[in] keyLength O tamanho da chave.
 * @param[in] operationType O tipo de operação (Encrypt ou Decrypt).
 */
void aesBlock(unsigned char *state, unsigned char *roundkey, short keyLength, enum OperationType operationType)
{
  short rounds = getRoundsCount(keyLength);
  int i;

  if (rounds == -1)
  {
    printf("Erro ao obter o número de rounds.\n");
    return;
  }

  if (operationType == Encrypt)
  {
    addRoundKey(state, roundkey); // Adição da chave de rodada
    for (i = 0; i < rounds; i++)
    {
      byteSub(state, operationType);  // Substituição de bytes
      shiftRow(state, operationType); // Deslocamento de linhas
      if (i < rounds - 1)
      {
        mixColumn(state, operationType); // Mistura de colunas
      }
      expandeKey(roundkey, i + 1);  // Expansão da chave
      addRoundKey(state, roundkey); // Adição da chave de rodada
    }
  }
  else
  {
    unsigned char roundkeyRound[rounds + 1][16];

    // Salva a chave da rodada 0
    for (i = 0; i < 16; i++)
    {
      roundkeyRound[0][i] = roundkey[i];
    }

    // Obtém todas as chaves da rodada
    for (i = 1; i <= rounds; i++)
    {
      expandeKey(roundkey, i);
      for (int j = 0; j < 16; j++)
      {
        roundkeyRound[i][j] = roundkey[j];
      }
    }

    addRoundKey(state, roundkeyRound[rounds]);

    for (i = rounds - 1; i >= 0; i--)
    {
      shiftRow(state, operationType);       // Deslocamento de linhas
      byteSub(state, operationType);        // Substituição de bytes
      addRoundKey(state, roundkeyRound[i]); // Adição da chave de rodada

      if (i > 0)
      {
        mixColumn(state, operationType); // Mistura de colunas
      }
    }
  }
}

/**
 * @brief Criptografa ou descriptografa uma mensagem usando o algoritmo AES.
 *
 * Esta função é o ponto de partida para o algoritmo AES. Ela prepara os dados e
 * executa o algoritmo em blocos de dados. A operação é determinada pelo tipo
 * de operação especificado em `operationType`.
 *
 * @param[in,out] data Um ponteiro para o vetor de dados a ser processado.
 * @param[in] operationType O tipo de operação (Encrypt ou Decrypt).
 * @param[in] key A chave a ser usada na operação.
 * @return 0 se a operação foi bem-sucedida, -1 em caso de erro.
 */
int aes(unsigned char **data, enum OperationType operationType, const char *key)
{
  unsigned char roundkey[16];
  short keyLength = getKeyLength(key);
  uint32_t dataSize = getDataSize(*data);
  int blocks = getBlockCount(dataSize, operationType);
  unsigned char stateBlocks[blocks][16];

  if (keyLength == -1)
  {
    return -1;
  }

  // Modo de operação.
  ecb(data, stateBlocks, dataSize, operationType);

  // Deriva a chave
  keyLength = deriveKey(key, roundkey, keyLength);

  for (int i = 0; i < blocks; i++)
  {
    aesBlock(stateBlocks[i], roundkey, keyLength, operationType);
  }

  // Modo de operação.
  invEcb(stateBlocks, dataSize, data, blocks, operationType);

  return 0;
}

#endif /* AES_H */
