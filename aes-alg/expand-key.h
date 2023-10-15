#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/**
 * @brief Converte um vetor de 16 bytes em uma matriz 4x4.
 *
 * @param key Vetor de 16 bytes a ser convertido.
 * @param matrix Matriz 4x4 que armazenará o resultado da conversão.
 */
void vectorToMatrix(unsigned char *key, unsigned char matrix[4][4])
{
  int i, j, k = 0;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      matrix[j][i] = (unsigned char)key[k];
      k++;
    }
  }
}

/**
 * @brief Converte uma matriz 4x4 em um vetor de 16 bytes.
 *
 * @param matrix Matriz 4x4 a ser convertida.
 * @param key Vetor de 16 bytes que armazenará o resultado da conversão.
 */
void matrixToVector(const unsigned char matrix[4][4], unsigned char key[])
{
  int i, j, k = 0;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      key[k] = matrix[j][i];
      k++;
    }
  }
}

/**
 * @brief Realiza um deslocamento circular em 4 bytes semelhante à função Shift Row.
 *
 * @param matrix Matriz 4x4 na qual o deslocamento é aplicado.
 * @param g Vetor de 4 bytes que armazenará o resultado do deslocamento.
 */
void RotWord(unsigned char matrix[4][4], unsigned char g[4])
{
  for (int i = 0; i < 3; i++)
  {
    // Copia os elementos da última linha da matriz no vetor g
    g[i] = matrix[i + 1][3];
  }
  g[3] = matrix[0][3];
}

/**
 * @brief Aplica a substituição do valor S-box a cada um dos 4 bytes no argumento.
 *
 * @param g Vetor de 4 bytes nos quais a substituição S-box será aplicada.
 */
void SubWord(unsigned char g[4])
{
  int x, y;
  for (int i = 0; i < 4; i++)
  {
    extractXY(g[i], &x, &y);
    g[i] = sBox[x][y];
  }
}

/**
 * @brief Calcula o valor do Round Constant usado na expansão da chave do algoritmo AES com base no round.
 *
 * @param round O round para o qual o valor Round Constant é calculado.
 * @param g Vetor de 4 bytes no qual o valor Round Constant é armazenado.
 */
void getRoundConstant(int round, unsigned char g[4])
{
  unsigned int result = 0;

  // Use um switch para determinar o valor com base no round
  switch (round)
  {
  case 1:
    result = 0x01;
    break;
  case 2:
    result = 0x02;
    break;
  case 3:
    result = 0x04;
    break;
  case 4:
    result = 0x08;
    break;
  case 5:
    result = 0x10;
    break;
  case 6:
    result = 0x20;
    break;
  case 7:
    result = 0x40;
    break;
  case 8:
    result = 0x80;
    break;
  case 9:
    result = 0x1B;
    break;
  case 10:
    result = 0x36;
    break;

  default:
    // Valor padrão caso o round seja inválido
    result = 0x00000000;
  }

  // Realize a operação XOR com todos os elementos da matriz matrix

  g[0] = g[0] ^ result;
}

/**
 * @brief Realiza operações de combinação final para expandir a chave.
 *
 * @param matrix Matriz 4x4 na qual as operações de combinação final são aplicadas.
 * @param g Vetor de 4 bytes usado nas operações de combinação.
 */
void end(unsigned char matrix[4][4], unsigned char g[4])
{
  // Faz o XOR entre a primeira linha e o vetor g
  for (int j = 0; j < 4; j++)
  {
    matrix[j][0] ^= g[j];
  }

  // Faz o XOR com as linhas subsequentes
  for (int i = 1; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      matrix[j][i] ^= matrix[j][i - 1];
    }
  }
}
/**
 * @brief Expande a chave de criptografia usando as funções definidas na especificação AES.
 *
 * @param key A chave original a ser expandida.
 * @param round O round atual da expansão da chave.
 */
void expandeKey(unsigned char *key, short round)
{
  unsigned char matrix[4][4];
  unsigned char g[4];
  vectorToMatrix(key, matrix);
  RotWord(matrix, g);
  SubWord(g);
  getRoundConstant(round, g);
  end(matrix, g);
  matrixToVector(matrix, key);
}