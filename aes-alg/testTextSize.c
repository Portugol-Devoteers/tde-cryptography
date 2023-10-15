#include <stdio.h>
#include <stdint.h>

// Função para converter bytes em uint32_t
uint32_t bytesToUInt(const unsigned char byteArray[4])
{
  uint32_t value = 0;
  value |= ((uint32_t)byteArray[0] << 24);
  value |= ((uint32_t)byteArray[1] << 16);
  value |= ((uint32_t)byteArray[2] << 8);
  value |= byteArray[3];
  return value;
}

// Função para converter uint32_t em bytes
void uintToBytes(uint32_t value, unsigned char byteArray[4])
{
  byteArray[0] = (value >> 24) & 0xFF;
  byteArray[1] = (value >> 16) & 0xFF;
  byteArray[2] = (value >> 8) & 0xFF;
  byteArray[3] = value & 0xFF;

  // invert
}

int main()
{
  uint32_t originalValue = 20; // Valor a ser armazenado
  printf("Valor original: %u\n", originalValue);

  unsigned char byteArray[4];

  // Convertendo o valor em bytes
  uintToBytes(originalValue, byteArray);

  printf("Bytes: %u %u %u %u\n", byteArray[0], byteArray[1], byteArray[2], byteArray[3]);

  // Recuperando o valor a partir dos bytes
  uint32_t retrievedValue = bytesToUInt(byteArray);

  printf("Valor recuperado: %u\n", retrievedValue);

  return 0;
}
