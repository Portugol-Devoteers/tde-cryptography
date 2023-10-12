#include <stdio.h>
void VparaM(unsigned char chave[], unsigned char M[4][4])
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
int main()
{
  unsigned char M[4][4];
  unsigned char chave[] = "0123456789ABCDEF";

  VparaM(chave, M);
  MparaV(M, chave);

  return 0;
}