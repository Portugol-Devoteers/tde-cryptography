#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aes.h"
#include "utils.h"
#include <stdint.h>

#ifndef PROGRAM_VERSION // Fazendo isso é possível usar macro como se fosse váriaveis ambiente
#define PROGRAM_VERSION "1.0.0"
#endif

#ifndef PROGRAM_AUTHORS
#define PROGRAM_AUTHORS "Lucas Carmona, Pedro Bonifacio, Lucas Cerqueira, Felipe Barbosa, Gustavo Silvestre"
#endif

#ifndef PROGRAM_GITHUB_REPO
#define PROGRAM_GITHUB_REPO "https://github.com/lucascarmon4/tde-cryptography"
#endif

/* Funções que compõe o programa CLI */

void printHelp()
{
  printf("Uso: programa [opções]\n");
  printf("Opções:\n");
  printf("  --text <texto>   Texto a ser processado\n");
  printf("  --key <chave>    Chave de criptografia\n");
  printf("  --action <1 ou -1>   Ação a ser executada (1 para criptografia, -1 para descriptografia)\n");
  printf("  --help            Exibe esta mensagem de ajuda\n");
  printf("  --version         Exibe informações da versão\n");
}

void printVersion()
{
  printf("Versão: %s\n", PROGRAM_VERSION);
  printf("Autores: %s\n", PROGRAM_AUTHORS);
  printf("Repositório no GitHub: %s\n", PROGRAM_GITHUB_REPO);
}

int validateArguments(const char *text, const char *key, int action)
{
  if (text == NULL || key == NULL || (action != 1 && action != -1))
  {
    return 0; // Comando inválido
  }
  return 1; // Comando válido
}

void printErrorMessage(const char *message)
{
  printf("Erro: %s. Use --help para obter ajuda.\n", message);
}

int validateStringParam(int i, int argc, char *argv[], const char *paramName, char **paramValue)
{
  if (i < argc)
  {
    *paramValue = argv[i];
    return 1;
  }
  else
  {
    printErrorMessage(strcat("Falta o valor para o parâmetro ", paramName));
    return 0;
  }
}

/* ------- */

/**
 * Função que conecta o programa com a biblioteca aes.h
 *
 * @param text O texto.
 * @param key A chave.
 * @param action A ação a ser executada (1 para criptografia, -1 para descriptografia).
 * @param result O ponteiro para o resultado.
 * @return 0 se a operação foi bem-sucedida, 1 se a operação falhou, 2 se houve erro de alocação de memória, 3 se houve erro ao adicionar o tamanho dos dados, 4 se houve erro ao transformar os gexs para string
 */
int aes_api(const char *text, const char *key, int action, char **result)
{
  uint32_t dataSize = strlen(text);
  unsigned char *data = (unsigned char *)malloc(dataSize * sizeof(unsigned char));

  if (data == NULL)
  {
    printf("Erro de alocação de memória.\n");
    return 2; // Erro de alocação de memória
  }

  // 1. Converta o texto para bytes
  if (action == 1)
  {
    // Se for criptografia, adicione 4 bytes para armazenar o tamanho dos dados
    // Descriptografia não precisa disso, porque o tamanho dos dados é já está armazenado no text
    if (addSizePrefix(&data, dataSize) != 1)
    {
      free(data);
      return 3; // Erro ao adicionar tamanho dos dados
    }
    dataSize += 4;
    // Converte o texto para bytes
    stringToBytes(text, dataSize, &data, 4);
  }
  else
  {
    // Se for descriptografia, decodifica tranforma a string de hexadecimais em um vetor de bytes
    hexStringToBytes(text, dataSize, &data);
    if (data == NULL)
    {
      printf("Erro ao transformar string.\n");
      return 4; // Erro ao transformar
    }
  }

  // 2. Executa o AES
  aes(&data, action, key);

  // 3. Retorna o resultado
  size_t dataSizeResult = bytesToUInt(data);
  if (action == -1)
  {
    // Remova o tamanho dos dados
    removeSizePrefix(&data);
    // Converte o resultado para plaintext
    *result = bytesToString(data, dataSizeResult);
  }
  else
  {
    // Se for criptografia, converte o resultado para string de bytes
    dataSizeResult += 4; // bytes que representam o tamanho dos dados
    *result = bytesToHexString(data, dataSizeResult);

    if (result == NULL)
    {
      free(data);
      printf("Erro ao transformar string.\n");
      return 4; // Erro ao codificar em base64
    }
  }

  // Limpa a memória
  free(data);

  return 0; // Sucesso
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printErrorMessage("Faltam argumentos");
    return 1;
  }

  char *text = NULL;
  char *key = NULL;
  char *action = NULL;

  // Processa os argumentos
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "--help") == 0)
    {
      printHelp();
      return 0;
    }
    else if (strcmp(argv[i], "--version") == 0)
    {
      printVersion();
      return 0;
    }
    else if (strcmp(argv[i], "--text") == 0)
    {
      i++;
      if (validateStringParam(i, argc, argv, "--text", &text) == 0)
      {
        return 1;
      }
    }
    else if (strcmp(argv[i], "--key") == 0)
    {
      i++;
      if (validateStringParam(i, argc, argv, "--key", &key) == 0)
      {
        return 1;
      }
    }
    else if (strcmp(argv[i], "--action") == 0)
    {
      i++;
      if (validateStringParam(i, argc, argv, "--action", &action) == 0)
      {
        return 1;
      }
    }
  }
  int actionInt = atoi(action);
  if (!validateArguments(text, key, actionInt))
  {
    printErrorMessage("Comando inválido");
    return 1;
  }

  char *result = NULL;

  if (aes_api(text, key, actionInt, &result) == 0)
  {
    printf("%s\n", result);
  }
  // Limpa a memória
  free(result);
  return 0;
}