#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define BLOCK_SIZE 16

/**
 * Função que realiza a operação xor entre dois vetores de BLOCK_SIZE bytes.
 *
 * @param state O state a ser substituido.
 * @param key A chave a ser utilizada na operação.
 * @return void - O state é substituido diretamente.
 */
void addRoundKey(unsigned char *state, unsigned char *key)
{
  for (int index = 0; index < BLOCK_SIZE; index++)
  {
    state[index] ^= key[index];
  }
}

/**
 * Substitui cada valor do state por o valor correspondente no S-box (operationType = 1 (normal) ou -1 (invertida)
 *
 * @param state O state a ser substituido.
 * @param operationType 1 para substituir, -1 para substituir invertido.
 * @return void - O state é substituido diretamente.
 */
void byteSub(unsigned char *state, enum OperationType operationType)
{
  for (int index = 0; index < BLOCK_SIZE; index++)
  {
    int line, collumn;
    extractXY(state[index], &line, &collumn);
    state[index] = operationType == 1 ? sBox[line][collumn] : invSBox[line][collumn];
  }
}

#define COLUMNS 4
typedef struct
{
  unsigned value : COLUMNS; // 4 bits
} state_index;

#define addValue(n, qt) n.value += qt

/**
 * Função que embaralha as linhas do state.
 * @param state O state a ser embaralhado.
 * @param operationType 1 para embaralhar, -1 para desembaralhar.
 * @return void - O state é substituido diretamente.
 */
void shiftRow(unsigned char *state, enum OperationType operationType)
{
  int line, collumn, repeatTime;
  unsigned char aux, oldVal;

  for (line = 0; line < COLUMNS; line++)
  {
    for (repeatTime = 0; repeatTime < line; repeatTime++)
    {
      state_index i = {line};

      oldVal = state[i.value];

      for (collumn = 0; collumn <= COLUMNS; collumn++)
      {
        aux = state[i.value];

        state[i.value] = oldVal;

        oldVal = aux;

        addValue(i, COLUMNS * (-operationType));
      }
    }
  }
}

/**
 * Realiza a soma de dois valores de acordo com uma tabela de substituição
 * e retorna o resultado dessa soma.
 *
 * @param n1 O primeiro valor a ser somado.
 * @param n2 O segundo valor a ser somado.
 * @param table A tabela de substituição (E-Table ou L-Table) usada para a soma.
 *
 * @return O valor resultante da soma, obtido a partir da tabela de substituição.
 *         Esse valor é calculado somando-se n1 e n2, ajustando o resultado se ele
 *         exceder 0xFF e, em seguida, consultando a tabela de substituição para obter
 *         o valor final.
 */
unsigned char sumWithEorL(unsigned char n1, unsigned char n2)
{
  if (n1 == 0)
    return 0;

  unsigned int lSum = getEorLValue(n1, lTable) + getEorLValue(n2, lTable);

  if (lSum > 0xFF)
    lSum -= 0xFF;

  return getEorLValue((unsigned char)lSum, eTable);
}

/**
 * Função que realiza a operação de multiplicação de matrizes.
 * @param state O state a ser embaralhado.
 * @param operationType 1 para criptografia, -1 para descriptografia.
 * @return void - O state é substituido diretamente.
 */
void mixColumn(unsigned char *state, enum OperationType operationType)
{
  const unsigned char(*matrix)[4] = operationType == Encrypt ? multiplicationMatrixEncrypt : multiplicationMatrixDecrypt;

  for (int j = 0; j < 4; j++)
  {
    short stateIndex;

    for (int i = 0; i < 4; i++)
    {
      stateIndex = i + (4 * j);

      unsigned char xorResult = 0;
      for (int k = 0; k < 4; k++)
      {
        xorResult ^= sumWithEorL(state[stateIndex], matrix[i][k]);
      }

      state[stateIndex] = xorResult;
    }
  }
}
