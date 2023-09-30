#include <stdio.h>
#include "core.h"

void addRoundKeyTest()
{
  unsigned char state[16] = {0x53, 0x6F, 0x6D, 0x65, 0x20, 0x74, 0x65, 0x78, 0x74, 0x20, 0x68, 0x65, 0x72, 0x65, 0x20, 0x31};
  unsigned char key[16] = {0x53, 0x6F, 0x6D, 0x65, 0x20, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x20, 0x6B, 0x65, 0x79, 0x31};
  unsigned char expectXor[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x1B, 0x06, 0x45, 0x1C, 0x45, 0x19, 0x00, 0x59, 0x00};

  addRoundKey(state, key);
  for (int i = 0; i < 16; i++)
  {
    if (state[i] != expectXor[i])
    {
      printf("addRoundKeyTest failed\n");

      printf("receive: ");
      for (int j = 0; j < 16; j++)
      {
        printf("%02X ", state[j]);
      }
      printf("\n");

      printf("expected: ");
      for (int j = 0; j < 16; j++)
      {
        printf("%02X ", expectXor[j]);
      }
      printf("\n");

      return;
    }
  }
  printf("addRoundKeyTest passed\n");
}

int main()
{
  addRoundKeyTest();
  return 0;
}