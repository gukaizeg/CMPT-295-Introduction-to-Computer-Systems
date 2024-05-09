#ifndef HELPER_H
#define HELPER_H

#include "intrin.h"
#include <stdio.h>

// void initValue(float *values, int *exponents, float *output, float *gold,
//                unsigned int N) {

//   for (unsigned int i = 0; i < N + VLEN; i++) {
//     // random input values
//     values[i] = -1.f - 0.01f * static_cast<float>(rand()) / RAND_MAX;
//     exponents[i] = rand() % EXP_MAX;
//     output[i] = 0.f;
//     gold[i] = 0.f;
//   }
// }

bool verifyfloat(float *values, float *output, float *gold,
                 int N) {
  int incorrect = -1;
  float epsilon = 0.00001;
  for (int i = 0; i < N + VLEN; i++) {
    if (abs(output[i] - gold[i]) > epsilon) {
      incorrect = i;
      break;
    }
  }

  if (incorrect != -1) {
    if (incorrect >= N) {
      printf("You have written to out of bound value!\n");
    }
    printf("Wrong calculation at value[%d]!\n", incorrect);
    printf("value  = ");

    printf("output = ");
    for (int i = 0; i < N; i++) {
      printf("% f ", output[i]);
    }
    printf("\n");

    printf("gold   = ");
    for (int i = 0; i < N; i++) {
      printf("% f ", gold[i]);
    }
    printf("\n");
    return false;
  }
  printf("Results matched with answer!\n");
  return true;
}

bool verifyint(int *values, int *output, int *gold, int N) {
  int incorrect = -1;
  for (int i = 0; i < N + VLEN; i++) {
    if (output[i] != gold[i]) {
      incorrect = i;
      break;
    }
  }

  if (incorrect != -1) {
    if (incorrect >= N) {
      printf("You have written to out of bound value!\n");
    }
    printf("Wrong calculation at value[%d]!\n", incorrect);
    printf("value  = ");
    for (int i = 0; i < N; i++) {
      printf("% d ", values[i]);
    }
    printf("\n");
    printf("output = ");
    for (int i = 0; i < N; i++) {
      printf("% d ", output[i]);
    }
    printf("\n");

    printf("gold   = ");
    for (int i = 0; i < N; i++) {
      printf("% d ", gold[i]);
    }
    printf("\n");
    return false;
  }
  printf("Results matched with answer!\n");
  return true;
}

#endif