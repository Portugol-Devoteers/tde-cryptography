#include <stdio.h>

extern void printHexVetor(unsigned char *vetor)
{
  for (int i = 0; i < 16; i++)
  {
    printf("%02X ", vetor[i]);
  }
  printf("\n");
}

extern void printReceiveExpect(unsigned char *receive, unsigned char *expect)
{
  printf("receive: ");
  printHexVetor(receive);

  printf("expected: ");
  printHexVetor(expect);

  printf("\n");
}

extern void printTestDescribe(char *testName)
{
  printf("Teste %s\n", testName);
  printf("========================================\n");
}

extern void printTestResult(int result)
{
  if (result == 0)
  {
    printf("Teste falhou\n");
  }
  else
  {
    printf("Teste passou\n");
  }
}

extern void eqVetor(unsigned char *receive, unsigned char *expect)
{
  int j;
  for (j = 0; j < 16; j++)
  {
    if (receive[j] != expect[j])
    {
      printTestResult(0);

      printReceiveExpect(receive, expect);
      return;
    }
  }
  printTestResult(1);
}