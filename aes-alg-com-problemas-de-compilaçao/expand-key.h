#ifndef EXPAND_KEY_H
#define EXPAND_KEY_H

/**
 * @brief Converte um vetor de 16 bytes em uma matriz 4x4.
 *
 * @param key Vetor de 16 bytes a ser convertido.
 * @param matrix Matriz 4x4 que armazenará o resultado da conversão.
 */
void vectorToMatrix(unsigned char *key, unsigned char matrix[4][4]);

/**
 * @brief Converte uma matriz 4x4 em um vetor de 16 bytes.
 *
 * @param matrix Matriz 4x4 a ser convertida.
 * @param key Vetor de 16 bytes que armazenará o resultado da conversão.
 */
void matrixToVector(const unsigned char matrix[4][4], unsigned char key[]);

/**
 * @brief Realiza um deslocamento circular em 4 bytes semelhante à função Shift Row.
 *
 * @param matrix Matriz 4x4 na qual o deslocamento é aplicado.
 * @param g Vetor de 4 bytes que armazenará o resultado do deslocamento.
 */
void RotWord(unsigned char matrix[4][4], unsigned char g[4]);

/**
 * @brief Aplica a substituição do valor S-box a cada um dos 4 bytes no argumento.
 *
 * @param g Vetor de 4 bytes nos quais a substituição S-box será aplicada.
 */
void SubWord(unsigned char g[4]);

/**
 * @brief Calcula o valor do Round Constant usado na expansão da chave do algoritmo AES com base no round.
 *
 * @param round O round para o qual o valor Round Constant é calculado.
 * @param g Vetor de 4 bytes no qual o valor Round Constant é armazenado.
 */
void getRoundConstant(int round, unsigned char g[4]);

/**
 * @brief Realiza operações de combinação final para expandir a chave.
 *
 * @param matrix Matriz 4x4 na qual as operações de combinação final são aplicadas.
 * @param g Vetor de 4 bytes usado nas operações de combinação.
 */
void end(unsigned char matrix[4][4], unsigned char g[4]);

/**
 * @brief Expande a chave de criptografia usando as funções definidas na especificação AES.
 *
 * @param key A chave original a ser expandida.
 * @param round O round atual da expansão da chave.
 */
void expandeKey(unsigned char *key, short round);

#endif /* EXPAND_KEY_H */
