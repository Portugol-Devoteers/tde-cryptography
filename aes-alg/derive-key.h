#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

short deriveKey(const char *key, unsigned char *derivedKey, short keyLength)
{
    // Converter a chave de const char * para unsigned char *
    short keySizeOutput = getNearestKeySize(keyLength);

    for (int i = 0; i < keyLength; i++)
    {
        derivedKey[i] = (unsigned char)key[i];
    }
    if (keySizeOutput - keyLength > 0)
    {
        // Calcula o número de bytes que precisam ser preenchidos
        int paddingLenght = keySizeOutput - keyLength;

        // Preenche a chave com zeros à direita
        memset(derivedKey + keyLength, 0, paddingLenght);
        return keySizeOutput; // retorna o novo comprimento da chave
    }
    return keyLength;
}
