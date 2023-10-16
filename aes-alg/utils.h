#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Função que extrai os valores de x (primeiros 4 bits a esquerda) e y (ultimos 4 bits) de um número hexadecimal.
 * @param hex O número hexadecimal a ser extraído.
 * @param x O valor de x a ser retornado.
 * @param y O valor de y a ser retornado.
 * @return void - Os valores de x e y são retornados por referência.
 */
void extractXY(unsigned char hex, int *x, int *y);

/**
 * @brief Realoca a memória de um vetor com um ponteiro para ponteiro.
 *
 * Esta função realoca a memória do vetor representado por um ponteiro para ponteiro
 * para o novo tamanho especificado. Se a realocação for bem-sucedida, o ponteiro
 * original é atualizado para apontar para a nova memória alocada. Caso contrário,
 * uma mensagem de erro é exibida.
 *
 * @param[in,out] vector O ponteiro para ponteiro que representa o vetor a ser realocado.
 * @param[in] newVectorSize O novo tamanho desejado para o vetor.
 */
void reallocMemory(unsigned char **vector, uint32_t newVectorSize);

/**
 * @brief Obtém um valor da tabela E ou L com base no valor fornecido.
 *
 * Esta função obtém um valor da tabela E ou L com base em um valor de entrada `n`.
 * A tabela usada é especificada pelo parâmetro `table`.
 *
 * @param[in] n O valor de entrada.
 * @param[in] table A tabela a ser usada (E ou L).
 * @return O valor correspondente da tabela.
 */
unsigned char getEorLValue(unsigned char n, const unsigned char (*table)[16]);

/**
 * @brief Remove bytes de um vetor de dados.
 *
 * Esta função remove um número especificado de bytes de um vetor de dados.
 * Os bytes a serem removidos são especificados pelo parâmetro `bytesToRemove`.
 *
 * @param[in,out] data O ponteiro para o vetor de dados.
 * @param[in] dataSize O tamanho atual do vetor de dados.
 * @param[in] bytesToRemove O número de bytes a serem removidos.
 */
void removeBytes(unsigned char **data, uint32_t dataSize, short bytesToRemove);

/**
 * @brief Obtém o tamanho da chave a partir de uma string de chave.
 *
 * Esta função calcula o tamanho da chave com base na string de chave fornecida.
 *
 * @param[in] key A string de chave.
 * @return O tamanho da chave.
 */
short getKeyLength(const char *key);

/**
 * @brief Obtém o tamanho mais próximo para a chave com base em um valor x.
 *
 * Esta função retorna o tamanho de chave mais próximo com base em um valor x fornecido.
 *
 * @param[in] x O valor usado para determinar o tamanho da chave.
 * @return O tamanho de chave mais próximo.
 */
unsigned char getNearestKeySize(unsigned char x);

/**
 * @brief Converte um array de bytes em um valor uint32_t.
 *
 * Esta função converte um array de 4 bytes em um valor uint32_t.
 *
 * @param[in] byteArray O array de bytes a ser convertido.
 * @return O valor uint32_t resultante.
 */
uint32_t bytesToUInt(const unsigned char byteArray[4]);

/**
 * @brief Converte um valor uint32_t em um array de bytes.
 *
 * Esta função converte um valor uint32_t em um array de 4 bytes.
 *
 * @param[in] value O valor uint32_t a ser convertido.
 * @param[out] byteArray O array de bytes resultante.
 */
void uintToBytes(uint32_t value, unsigned char byteArray[4]);

/**
 * @brief Obtém o número de rodadas com base no tamanho da chave.
 *
 * Esta função determina o número de rodadas com base no tamanho da chave.
 *
 * @param[in] keyLength O tamanho da chave.
 * @return O número de rodadas.
 */
short getRoundsCount(short keyLength);

#endif // UTILS_H
