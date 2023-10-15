#include "utils.h"

void extractXY(unsigned char hex, int *x, int *y)
{
    // Extrai o primeiro dígito (4 bits mais significativos) como x
    *x = (hex >> 4) & 0xF;

    // Extrai o segundo dígito (4 bits menos significativos) como y
    *y = hex & 0xF;
}

void reallocMemory(unsigned char **vector, uint32_t newVectorSize)
{
    unsigned char *newVector = (unsigned char *)realloc(*vector, newVectorSize * sizeof(unsigned char));
    if (newVector != NULL)
    {
        *vector = newVector; // Atualiza o ponteiro original
    }
    else
    {
        printf("Algo deu errado ao realocar a memória.\n");
    }
}

unsigned char getEorLValue(unsigned char n, const unsigned char (*table)[16])
{
    int x, y;
    extractXY(n, &x, &y);

    return table[x][y];
}

void removeBytes(unsigned char **data, uint32_t dataSize, short bytesToRemove)
{
    u_int32_t vectorSize = dataSize + bytesToRemove;
    // Inicie a partir da posição onde os bytes devem ser removidos
    size_t copySize = vectorSize - bytesToRemove; // Tamanho do trecho a ser copiado

    // Usando memcpy para copiar o trecho de data
    memcpy(*data, *data + bytesToRemove, copySize);
    // realloc
    reallocMemory(data, vectorSize - bytesToRemove);
}

short getKeyLength(const char *key)
{
    if (key == NULL)
    {
        printf("Erro ao obter o tamanho da chave.\n");
        return -1;
    }

    return (short)strlen(key);
}

unsigned char getNearestKeySize(unsigned char x)
{
    if (x <= 16)
    {
        return 16;
    }
    else if (x <= 24)
    {
        return 24;
    }
    else
    {
        return 32;
    }
}

uint32_t bytesToUInt(const unsigned char byteArray[4])
{
    uint32_t value = 0;
    value |= ((uint32_t)byteArray[0] << 24);
    value |= ((uint32_t)byteArray[1] << 16);
    value |= ((uint32_t)byteArray[2] << 8);
    value |= byteArray[3];
    return value;
}

void uintToBytes(uint32_t value, unsigned char byteArray[4])
{
    byteArray[0] = (value >> 24) & 0xFF;
    byteArray[1] = (value >> 16) & 0xFF;
    byteArray[2] = (value >> 8) & 0xFF;
    byteArray[3] = value & 0xFF;
}

short getRoundsCount(short keyLength)
{
    switch (keyLength)
    {
    case 16:
        return 10;
    case 24:
        return 12;
    case 32:
        return 14;
    default:
        return -1;
    }
}
