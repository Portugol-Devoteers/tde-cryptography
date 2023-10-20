#include <stdio.h>
#include "../core.h"
#include "test.utils.h"

void addRoundKeyTest()
{
  printTestDescribe("addRoundKeyTest");

  unsigned char state[16] = {0x53, 0x6F, 0x6D, 0x65, 0x20, 0x74, 0x65, 0x78, 0x74, 0x20, 0x68, 0x65, 0x72, 0x65, 0x20, 0x31};
  unsigned char key[16] = {0x53, 0x6F, 0x6D, 0x65, 0x20, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x20, 0x6B, 0x65, 0x79, 0x31};
  unsigned char expectXor[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x1B, 0x06, 0x45, 0x1C, 0x45, 0x19, 0x00, 0x59, 0x00};

  addRoundKey(state, key);
  eqVetor(state, expectXor, 16);

  printf("========================================\n\n\n");
}

void byteSubTest()
{
  printTestDescribe("byteSubTest");
  // 9d2c755c8d4ecb890d45e138b8025859

  unsigned char expectEncrypt[] =
      {0x9d, 0x2c, 0x75, 0x5c, 0x8d, 0x4e, 0xcb, 0x89, 0x0d, 0x45, 0xe1, 0x38, 0xb8, 0x02, 0x58, 0x59};
  unsigned char expectDecrypt[] =
      {0x36, 0x17, 0x59, 0xfd, 0x97, 0x1d, 0x08, 0xdc, 0x02, 0xf6, 0x3f, 0xf0, 0x30, 0x03, 0x81, 0x04};
  unsigned char stateEncrypt[] = {0x75, 0x42, 0x3F, 0xA7, 0xB4, 0xB6, 0x59, 0xF2, 0xF3, 0x68, 0xE0, 0x76, 0x9A, 0x6A, 0x5E, 0x15};
  unsigned char stateDescrypt[] = {0x05, 0xF0, 0xCB, 0x54, 0x88, 0xA4, 0x30, 0x86, 0x77, 0x42, 0x75, 0x8C, 0x04, 0x7B, 0x0C, 0xF2};

  int i;
  for (i = -1; i < 2; i += 2)
  {
    unsigned char state[16];
    unsigned char *expect;

    int operationType = i * -2 + i;
    if (operationType == 1)
    {
      printf("encrypt\n");
      memcpy(state, stateEncrypt, 16);
      expect = expectEncrypt;
    }
    else
    {
      printf("decrypt\n");
      memcpy(state, stateDescrypt, 16);
      expect = expectDecrypt;
    }

    byteSub(state, operationType);
    eqVetor(state, expect, 16);
  }
  printf("========================================\n\n\n");
}

void testShiftRow()
{
  printTestDescribe("testShiftRow");

  unsigned char expectEncrypt[] = {0x01, 0x06, 0x0B, 0x10,
                                   0x05, 0x0A, 0x0F, 0x04,
                                   0x09, 0x0E, 0x03, 0x08,
                                   0x0D, 0x02, 0x07, 0x0C};
  unsigned char expectDecrypt[] = {0x01, 0x0E, 0x0B, 0x08,
                                   0x05, 0x02, 0x0F, 0x0C,
                                   0x09, 0x06, 0x03, 0x10,
                                   0x0D, 0x0A, 0x07, 0x04};

  int i;
  for (i = -1; i < 2; i += 2)
  {
    unsigned char state[16] = {0x01, 0x02, 0x03, 0x04,
                               0x05, 0x06, 0x07, 0x08,
                               0x09, 0x0A, 0x0B, 0x0C,
                               0x0D, 0x0E, 0x0F, 0x10};
    unsigned char *expect;

    int operationType = i * -2 + i;
    if (operationType == 1)
    {
      printf("encrypt\n");
      expect = expectEncrypt;
    }
    else
    {
      printf("decrypt\n");
      expect = expectDecrypt;
    }

    shiftRow(state, operationType);
    eqVetor(state, expect, 16);
  }
  printf("========================================\n\n\n");
}

void testMixColumn()
{
  printTestDescribe("testMixColumn");

  unsigned char decryptState[] = {
      0x04, 0x66, 0x81, 0xE5,
      0xE0, 0xCB, 0x19, 0x9A,
      0x48, 0xF8, 0xD3, 0x7A,
      0x28, 0x06, 0x26, 0x4C};
  unsigned char encryptState[] = {
      0xD4, 0xBF, 0x5D, 0x30,
      0xE0, 0xB4, 0x52, 0xAE,
      0xB8, 0x41, 0x11, 0xF1,
      0x1E, 0x27, 0x98, 0xE5};
  unsigned char expectDecrypt[] = {
      0xD4, 0xBF, 0x5D, 0x30,
      0xE0, 0xB4, 0x52, 0xAE,
      0xB8, 0x41, 0x11, 0xF1,
      0x1E, 0x27, 0x98, 0xE5};
  unsigned char expectEncrypt[] = {
      0x04, 0x66, 0x81, 0xE5,
      0xE0, 0xCB, 0x19, 0x9A,
      0x48, 0xF8, 0xD3, 0x7A,
      0x28, 0x06, 0x26, 0x4C};

  int i;
  for (i = -1; i < 2; i += 2)
  {
    int operationType = i * -2 + i;

    if (operationType == 1)
    {
      printf("encrypt\n");
      mixColumn(encryptState, operationType);
      eqVetor(encryptState, expectEncrypt, 16);
    }
    else
    {
      printf("decrypt\n");
      mixColumn(decryptState, operationType);
      eqVetor(decryptState, expectDecrypt, 16);
    }
  }
  printf("========================================\n\n\n");
}

int main()
{
  addRoundKeyTest();
  byteSubTest();
  testShiftRow();
  testMixColumn();
  return 0;
}