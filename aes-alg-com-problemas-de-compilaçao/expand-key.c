#include "expand-key.h"
#include "includes.h"
#include "globals.h"

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

void RotWord(unsigned char matrix[4][4], unsigned char g[4])
{
  for (int i = 0; i < 3; i++)
  {
    // Copia os elementos da última linha da matriz no vetor g
    g[i] = matrix[i + 1][3];
  }
  g[3] = matrix[0][3];
}

void SubWord(unsigned char g[4])
{
  int x, y;
  for (int i = 0; i < 4; i++)
  {
    extractXY(g[i], &x, &y);
    g[i] = sBox[x][y];
  }
}

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
