#ifndef CORE_H
#define CORE_H



#define COLUMNS 4
#define addValue(n, qt) n.value += qt

typedef struct
{
  unsigned value : COLUMNS; // 4 bits
} state_index;

/**
 * Função que realiza a operação xor entre dois vetores de BLOCK_SIZE bytes.
 *
 * @param state O state a ser substituido.
 * @param key A chave a ser utilizada na operação.
 * @return void - O state é substituido diretamente.
 */
void addRoundKey(unsigned char *state, unsigned char *key);

/**
 * Substitui cada valor do state por o valor correspondente no S-box (operationType = 1 (normal) ou -1 (invertida)
 *
 * @param state O state a ser substituido.
 * @param operationType 1 para substituir, -1 para substituir invertido.
 * @return void - O state é substituido diretamente.
 */
void byteSub(unsigned char *state, short operationType);

/**
 * Função que embaralha as linhas do state.
 * @param state O state a ser embaralhado.
 * @param operationType 1 para embaralhar, -1 para desembaralhar.
 * @return void - O state é substituido diretamente.
 */
void shiftRow(unsigned char *state, short operationType);

/**
 * Realiza a soma de dois valores de acordo com uma tabela de substituição
 * e retorna o resultado dessa soma.
 *
 * @param n1 O primeiro valor a ser somado.
 * @param n2 O segundo valor a ser somado.
 * @param table A tabela de substituição (E-Table ou L-Table) usada para a soma.
 *
 * @return O valor resultante da soma, obtido a partir da tabela de substituição.
 *         Esse valor é calculado somando-se n1 e n2, ajustando o resultado se ele
 *         exceder 0xFF e, em seguida, consultando a tabela de substituição para obter
 *         o valor final.
 */
unsigned char sumWithEorL(unsigned char n1, unsigned char n2);

/**
 * Função que realiza a operação de multiplicação de matrizes.
 * @param state O state a ser embaralhado.
 * @param operationType 1 para criptografia, -1 para descriptografia.
 * @return void - O state é substituido diretamente.
 */
void mixColumn(unsigned char *state, short operationType);

#endif /* CORE_H */
