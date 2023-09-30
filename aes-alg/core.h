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
    state[i] ^= key[i];
  }
}

/**
 * Substitui cada valor do state por o valor correspondente no S-box (action = 1 (normal) ou -1 (invertida)
 *
 * @param state O state a ser substituido.
 * @param action 1 para substituir, -1 para substituir invertido.
 * @return void - O state é substituido diretamente.
 */
extern void byteSub(unsigned char *state, unsigned char action)
{
  for (int i = 0; i < 16; i++)
  {
    int x, y;
    extractXY(state[i], &x, &y);
    state[i] = action == 1 ? sBox[x][y] : invSBox[x][y];
  }
}