#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include "utils.h"

extern int deriveKey(char *key, unsigned char *derivedKey, unsigned char keyLength, unsigned char *salt, short action)
{
    unsigned char saltCopy[16];
    if (action == 1)
    {
        RAND_bytes(saltCopy, sizeof(saltCopy));
    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            saltCopy[i] = salt[i];
        }
    }

    int iterations = 10000;
    unsigned char keySize = nearestKeySize(keyLength);

    // Inicializar OpenSSL
    OpenSSL_add_all_algorithms();

    // Derivação da chave
    PKCS5_PBKDF2_HMAC(key, keyLength, saltCopy, sizeof(saltCopy), iterations, EVP_sha256(), (int)keySize, derivedKey);

    // copia o saltCopy para o salt
    for (int i = 0; i < 16; i++)
    {
        salt[i] = saltCopy[i];
    }

    // Limpar OpenSSL
    EVP_cleanup();

    return 0;
}
