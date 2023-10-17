#include "core.h"
#include "includes.h"
#include "globals.h"

void addRoundKey(unsigned char *state, unsigned char *key)
{
  for (int index = 0; index < BLOCK_SIZE; index++)
  {
    state[index] ^= key[index];
  }
}

void byteSub(unsigned char *state, short operationType)
{
  for (int index = 0; index < BLOCK_SIZE; index++)
  {
    int line, collumn;
    extractXY(state[index], &line, &collumn);
    state[index] = operationType == 1 ? sBox[line][collumn] : invSBox[line][collumn];
  }
}

void shiftRow(unsigned char *state, short operationType)
{
  int line, collumn, repeatTime;
  unsigned char aux, oldVal;

  for (line = 0; line < COLUMNS; line++)
  {
    for (repeatTime = 0; repeatTime < line; repeatTime++)
    {
      state_index i = {line};

      oldVal = state[i.value];

      for (collumn = 0; collumn <= COLUMNS; collumn++)
      {
        aux = state[i.value];

        state[i.value] = oldVal;

        oldVal = aux;

        addValue(i, COLUMNS * (-operationType));
      }
    }
  }
}

unsigned char sumWithEorL(unsigned char n1, unsigned char n2)
{
  if (n1 == 0)
    return 0;

  unsigned int lSum = getEorLValue(n1, lTable) + getEorLValue(n2, lTable);

  if (lSum > 0xFF)
    lSum -= 0xFF;

  return getEorLValue((unsigned char)lSum, eTable);
}

void mixColumn(unsigned char *state, short operationType)
{
  const unsigned char(*matrix)[4] = operationType == 1 ? multiplicationMatrixEncrypt : multiplicationMatrixDecrypt;

  for (int j = 0; j < 4; j++)
  {
    short stateIndex;

    for (int i = 0; i < 4; i++)
    {
      stateIndex = i + (4 * j);

      unsigned char xorResult = 0;
      for (int k = 0; k < 4; k++)
      {
        xorResult ^= sumWithEorL(state[stateIndex], matrix[i][k]);
      }

      state[stateIndex] = xorResult;
    }
  }
}
