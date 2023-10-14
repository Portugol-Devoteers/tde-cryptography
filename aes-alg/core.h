#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * Função que realiza a operação xor entre dois vetores de 16 bytes.
 *
 * @param state O state a ser substituido.
 * @param key A chave a ser utilizada na operação.
 * @return void - O state é substituido diretamente.
 */
extern void addRoundKey(unsigned char *state, unsigned char *key)
{
  for (int i = 0; i < 16; i++)
  {
    unsigned char aux = state[i];
    unsigned char aux2 = key[i]; // TODO undo this, used only for debug
    state[i] = aux ^ aux2;
  }
}

/**
 * Substitui cada valor do state por o valor correspondente no S-box (action = 1 (normal) ou -1 (invertida)
 *
 * @param state O state a ser substituido.
 * @param action 1 para substituir, -1 para substituir invertido.
 * @return void - O state é substituido diretamente.
 */
extern void byteSub(unsigned char *state, short action)
{
  for (int i = 0; i < 16; i++)
  {
    int x, y;
    extractXY(state[i], &x, &y);
    unsigned char aux = action == 1 ? sBox[x][y] : invSBox[x][y]; // TODO undo this, used only for debug
    state[i] = aux;
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
 * @param action 1 para embaralhar, -1 para desembaralhar.
 * @return void - O state é substituido diretamente.
 */
extern void shiftRow(unsigned char *state, short action)
{
  int line, col, repeatTime;
  unsigned char aux, oldVal;
  for (line = 0; line < COLUMNS; line++)
  {

    for (repeatTime = 0; repeatTime < line; repeatTime++)
    {
      state_index i = {line};

      oldVal = state[i.value];
      for (col = 0; col <= COLUMNS; col++)
      {
        aux = state[i.value];

        state[i.value] = oldVal;
        oldVal = aux;
        addValue(i, COLUMNS * (-action));
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

  unsigned char n1L = getEorLValue(n1, lTable);
  unsigned char n2L = getEorLValue(n2, lTable);
  unsigned int lSum = n1L + n2L;
  if (lSum > 0xFF)
    lSum -= 0xFF;
  return getEorLValue((unsigned char)lSum, eTable);
}

/**
 * Função que realiza a operação de multiplicação de matrizes.
 * @param state O state a ser embaralhado.
 * @param action 1 para embaralhar, -1 para desembaralhar.
 * @return void - O state é substituido diretamente.
 */
extern void mixColumn(unsigned char *state, short action)
{
  const unsigned char(*matrix)[4] = action == 1 ? multiplicationMatrixEncrypt : multiplicationMatrixDecrypt;
  for (int j = 0; j < 4; j++)
  {
    unsigned char aux[4];
    int stateIndex;
    for (int i = 0; i < 4; i++)
    {
      stateIndex = i + (4 * j);
      aux[i] = state[stateIndex];
    }

    for (int i = 0; i < 4; i++)
    {
      stateIndex = i + (4 * j);

      unsigned char colsXor = 0;
      for (int k = 0; k < 4; k++)
      {
        unsigned char r = sumWithEorL(aux[k], matrix[i][k]); // TODO undo this, used only for debug
        colsXor ^= r;
      }

      state[stateIndex] = colsXor;
    }
  }
}
