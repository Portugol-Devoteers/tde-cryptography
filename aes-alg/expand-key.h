#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void VparaM(unsigned char *chave, unsigned char M[4][4])
{
  int i, j, k = 0;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      M[j][i] = (unsigned char)chave[k];
      k++;
    }
  }
}
void MparaV(const unsigned char M[4][4], unsigned char chave[])
{
  int i, j, k = 0;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      chave[k] = M[j][i];
      k++;
    }
  }
}
void printM(unsigned char M[4][4])
{
  printf("Matriz 4x4 resultante:\n");
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      printf("%02X ", M[j][i]); // Imprime o valor hexadecimal do byte
    }
    printf("\n");
  }
}

void printG(unsigned char g[4])
{
  for (int i = 0; i < 4; i++)
  {
    printf("%02X ", g[i]);
  }
  printf("\n");
}

void RotWorld(unsigned char matrix[4][4], unsigned char g[4])
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

void Rcon(int round, unsigned char g[4])
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

  // Realize a operação XOR com todos os elementos da matriz M

  g[0] = g[0] ^ result;
}

void fim(unsigned char matrix[4][4], unsigned char g[4])
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

extern void expandeKey(unsigned char *chave, int round)
{
  unsigned char M[4][4];
  unsigned char g[4];
  VparaM(chave, M);
  RotWorld(M, g);
  SubWord(g);
  Rcon(round, g);
  fim(M, g);
  MparaV(M, chave);
}

// int main()
// {
//   int tamanho = 16; // Tamanho do vetor, ajuste conforme necessário
//   unsigned char *hex_values = (unsigned char *)malloc(tamanho * sizeof(unsigned char));
//   int round;

//   printf("Digite os valores hexadecimais separados por espaços: ");
//   for (int i = 0; i < tamanho; i++)
//   {
//     char hex_string[3];
//     if (scanf("%2s", hex_string) != 1)
//     {
//       printf("Erro ao ler entrada.\n");
//       free(hex_values);
//       return 1;
//     }
//     hex_values[i] = (unsigned char)strtol(hex_string, NULL, 16);
//   }

//   printf("Em qual round estamos: ");
//   scanf("%i", &round);

//   printf("\n\n\nFazer tudo isso com uma funcao apenas (expandeKey):\n\n");
//   expandeKey(hex_values, round);

//   free(hex_values);

//   return 0;
// }