
#ifndef AES_H
#define AES_H



/**
 * @file aes.h
 * @brief Arquivo de cabeçalho para funções relacionadas ao algoritmo AES.
 */

/**
 * @brief Realiza uma única operação AES em um bloco de dados.
 *
 * Esta função executa uma única operação AES (criptografia ou descriptografia) em um
 * bloco de dados representado pelo estado `state`. A operação é determinada pelo tipo
 * de operação especificado em `operationType`. A chave de rodada `roundkey` é usada
 * para a operação.
 *
 * @param[in,out] state O estado do bloco de dados a ser processado.
 * @param[in] roundkey A chave de rodada a ser usada na operação. Deve ter 16 bytes. Sempre é a chave de rodada 0.
 * @param[in] keyLength O tamanho da chave.
 * @param[in] operationType O tipo de operação (1 ou -1).
 */
void aesBlock(unsigned char *state, unsigned char *roundkey, short keyLength, short operationType);

/**
 * @brief Criptografa ou descriptografa uma mensagem usando o algoritmo AES.
 *
 * Esta função é o ponto de partida para o algoritmo AES. Ela prepara os dados e
 * executa o algoritmo em blocos de dados. A operação é determinada pelo tipo
 * de operação especificado em `operationType`.
 *
 * @param[in,out] data Um ponteiro para o vetor de dados a ser processado.
 * @param[in] operationType O tipo de operação (1 ou -1).
 * @param[in] key A chave a ser usada na operação.
 * @return 0 se a operação foi bem-sucedida, -1 em caso de erro.
 */
int aes(unsigned char **data, short operationType, char *key);

#endif /* AES_H */
