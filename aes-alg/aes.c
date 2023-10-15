
#include "aes.h"

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

int aes(unsigned char **data, enum OperationType operationType, char *key)
{
  unsigned char roundkey[16];
  short keyLength = getKeyLength(key);
  uint32_t dataSize = getDataSize(*data);
  int blocks = getBlockCount(dataSize, operationType);
  unsigned char stateBlocks[blocks][16];
  unsigned char *salt = (unsigned char *)malloc(16 * sizeof(unsigned char));

  if (keyLength == -1)
  {
    return -1;
  }

  // Modo de operação.
  ecb(data, stateBlocks, &salt, dataSize, operationType);

  // Deriva a chave
  deriveKey(key, roundkey, &keyLength, &salt, operationType);

  for (int i = 0; i < blocks; i++)
  {
    aesBlock(stateBlocks[i], roundkey, keyLength, operationType);
  }

  // Modo de operação.
  invEcb(stateBlocks, dataSize, data, blocks, &salt, operationType);

  // Limpa a memória
  free(salt);
  return 0;
}
