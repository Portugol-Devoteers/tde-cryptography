#include "derive-key.h"

int deriveKey(char *key, unsigned char *derivedKey, short *keyLength, unsigned char **salt, enum OperationType operationType)
{
    if (operationType == Encrypt)
    {
        RAND_bytes((*salt), sizeof((*salt)));
    }

    int iterations = 10000;
    short keySizeOutput = getNearestKeySize((*keyLength));

    // Inicializar OpenSSL
    OpenSSL_add_all_algorithms();

    // Derivação da chave
    PKCS5_PBKDF2_HMAC(key, (*keyLength), (*salt), sizeof((*salt)), iterations, EVP_sha256(), (int)keySizeOutput, derivedKey);

    (*keyLength) = keySizeOutput;
    // Limpar OpenSSL
    EVP_cleanup();

    return 0;
}
