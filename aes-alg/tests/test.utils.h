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
}

extern void createPlaintext(char *text, int maxSize)
{
  char loren[] = "Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32.";

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