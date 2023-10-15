#include <stdio.h>

extern void printHexVetor(unsigned char *vetor, short vetorSize)
{
  for (int i = 0; i < vetorSize; i++)
  {
    printf("%02X ", vetor[i]);
  }
  printf("\n\n");
}

extern void printReceiveExpect(unsigned char *receive, unsigned char *expect, short vetorSize)
{
  printf("receive: ");
  printHexVetor(receive, vetorSize);

  printf("expected: ");
  printHexVetor(expect, vetorSize);

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

extern void eqVetor(unsigned char *receive, unsigned char *expect, short vetorSize)
{
  int j;
  for (j = 0; j < vetorSize; j++)
  {
    if (receive[j] != expect[j])
    {
      printTestResult(0);

      printReceiveExpect(receive, expect, vetorSize);
      return;
    }
  }
  // printReceiveExpect(receive, expect, vetorSize);
  printTestResult(1);
}

extern void eqString(unsigned char *receive, unsigned char *expect, short stringSize)
{
  int j;
  for (j = 0; j < stringSize; j++)
  {
    if (receive[j] != expect[j])
    {
      printTestResult(0);

      printf("Bytes: \n");
      printReceiveExpect(receive, expect, stringSize);
      printf("String: \n");

      printf("receive: %s\n\n", receive);
      printf("expected: %s\n\n", expect);

      return;
    }
  }
  printf("receive: %s\n\n", receive);
  printf("expected: %s\n\n", expect);
  printTestResult(1);
}

extern void createPlaintext(char *text, int maxSize)
{
  char loren[] = "_YF20wocnOJZ1$ }{LiN_kFJmPraL_M>w;>;$?94^b=8Bn0}a4Ml.n8vEJ_[<8kF^10hm-W&i$}2H{\"\'\"%|Vk!My/FaqH/q\"5yC%L[$=WI\"g>zk/2f_YeH~/Bxv<j<EqHEUf=iT(6{nX:>FvX0 fZU!VN:km&eyPxjK&[$ThJZ3Uq7(pAN/x|*NE\'gbWDv43(gKTS-^Pdb9;2UICd^;*>U$}*/5vU$RNXZWpZ:Q!1=;@SzhieEdbo1x=xFvS6>q1/Jg>iYBEZ?,F 9%~qh?wg!a7K#c/x9f>N_{|#T#, jU%+]0\'GPXWDt,\\uiZU.m=2d+a\"|0T;Hb|mr1`{xXnXOYA:XVSd/(6j5y$Y8k> =z ,r;?eEkWz_tqBuu?@{T90=43Q\\hFo(arByVq!eK^3?mBQ>hf-DXy2LMSQMWuZ^ue~^-=t6T$m3FrWDC!-NJ=6.#2\'D0Zw/M8Y`</c9\'2bJ>[sj)oseOXw/Y*&UD2Z.\'(_uRf?(xdH";

  int textLength = strlen(loren);
  int copied = 0; // Rastreia o número de caracteres copiados

  // Copia o texto original para o ponteiro fornecido em partes
  while (copied < maxSize)
  {

    // Calcula o tamanho da próxima parte a ser copiada
    int partSize = (maxSize - copied) < textLength ? (maxSize - copied) : textLength;

    // Copia a parte atual do texto original
    strncpy(&text[copied], loren, partSize);

    copied += partSize;

    // Verifica se mais cópias são necessárias
    if (copied < maxSize)
    {
      text[copied] = '\n'; // Adiciona uma quebra de linha
      copied++;            // Incrementa para a próxima posição
    }
  }

  text[maxSize] = '\0'; // Garante que a string resultante seja terminada corretamente
}