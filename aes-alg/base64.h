#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string.h>

/**
 * @brief Codifica um array de bytes no formato Base64.
 *
 * Esta função codifica um array de bytes no formato Base64 usando a biblioteca OpenSSL e retorna a representação Base64 como uma string alocada dinamicamente.
 *
 * @param input Um ponteiro para o array de bytes a ser codificado no formato Base64.
 * @param length O tamanho do array de entrada.
 * @return Uma string contendo a representação Base64 dos dados, alocada dinamicamente. O chamador é responsável por liberar a memória alocada.
 *
 * @note A função utiliza um BIO (Buffer I/O) da biblioteca OpenSSL para realizar a codificação Base64.
 * @see https://www.openssl.org/docs/manmaster/man3/BIO_f_base64.html
 */
char *base64Encode(const unsigned char *input, int length)
{
  BIO *b64, *bio;
  BUF_MEM *bufferPtr;

  // Cria um BIO para codificação Base64
  b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Define as flags para não incluir quebras de linha

  // Cria um BIO de memória para armazenar o resultado da codificação
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  // Escreve os dados no BIO de codificação
  BIO_write(bio, input, length);
  BIO_flush(bio);

  // Obtém o ponteiro do buffer do BIO de memória
  BIO_get_mem_ptr(bio, &bufferPtr);

  // Aloca memória para a string codificada em Base64
  char *base64Data = (char *)malloc(bufferPtr->length + 1); // Adicione 1 para o terminador nulo
  if (base64Data == NULL)
  {
    // Lidar com erro de alocação de memória
    BIO_free_all(bio);
    return NULL;
  }

  // Copia os dados codificados para a string
  memcpy(base64Data, bufferPtr->data, bufferPtr->length);
  base64Data[bufferPtr->length] = '\0'; // Adicione o terminador nulo à string

  // Libera a memória alocada para os BIOs
  BIO_free_all(bio);

  return base64Data;
}

/**
 * @brief Decodifica uma string codificada em Base64 e armazena o resultado em um array de saída.
 *
 * Esta função utiliza os BIOs OpenSSL (Buffer I/O) para decodificar dados em Base64 a partir da string de entrada e armazena o resultado em um array de saída alocado dinamicamente. O tamanho real dos dados decodificados é armazenado na mesma variável 'length', que inicialmente representava o tamanho da entrada.
 *
 * @param input A string codificada em Base64 a ser decodificada.
 * @param length O comprimento da string codificada em Base64.
 * @param output Um ponteiro para o array que conterá os dados decodificados, alocado dinamicamente.
 */
void base64Decode(const char *input, uint32_t length, unsigned char **output)
{
  BIO *b64, *bio;
  size_t outputSize = length * 3 / 4; // Tamanho máximo possível após a decodificação

  // Cria um BIO para decodificação Base64
  b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Define as flags para não incluir quebras de linha

  // Cria um BIO de memória a partir da string de entrada
  bio = BIO_new_mem_buf(input, length);
  bio = BIO_push(b64, bio);

  // Aloca memória para os dados decodificados
  *output = (unsigned char *)malloc(outputSize);
  if (*output == NULL)
  {
    // Lidar com erro de alocação de memória
    BIO_free_all(bio);
    return;
  }

  // Realiza a decodificação e obtém o tamanho real dos dados decodificados
  int actualDecodedSize = BIO_read(bio, *output, length);

  if (actualDecodedSize < 0)
  {
    // Erro na decodificação
    free(*output);
    *output = NULL;
  }
  else
  {
    // Redimensiona o array para o tamanho real dos dados decodificados
    *output = (unsigned char *)realloc(*output, actualDecodedSize);
  }

  // Libera a memória alocada para os BIOs
  BIO_free_all(bio);
}