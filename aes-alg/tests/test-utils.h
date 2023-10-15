#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <string.h>

void printHexVetor(unsigned char *vetor, short vetorSize);

void printReceiveExpect(unsigned char *receive, unsigned char *expect, short vetorSize);

void printTestDescribe(char *testName);

void printTestResult(int result);

void eqVetor(unsigned char *receive, unsigned char *expect, short vetorSize);

void eqString(unsigned char *receive, unsigned char *expect, short stringSize);

void loren(char *text, int maxSize);

#endif /* TEST_UTILS_H */
