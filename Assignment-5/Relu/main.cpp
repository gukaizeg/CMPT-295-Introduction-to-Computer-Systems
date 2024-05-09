#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "Relu.h"
#include "dataset.h"
#include "helpers.h"
#include "intrin.h"
#include "logger.h"

using namespace std;

#define EXP_MAX 1024

Logger cs295Logger;

void usage(const char *progname);
void initValue(int *values, int *exponents, int *output, int *gold,
               unsigned int N);
bool verifyResult(int *values, int *exponents, int *output, int *gold, int N);

int main(int argc, char *argv[]) {
  bool printLog = false;

  // parse commandline options ////////////////////////////////////////////
  int opt;
  static struct option long_options[] = {
      {"log", 0, 0, 'l'}, {"help", 0, 0, '?'}, {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "s:l?", long_options, NULL)) != EOF) {
    switch (opt) {
      case 'l':
        printLog = true;
        break;
      case '?':
      default:
        usage(argv[0]);
        return 1;
    }
  }

  printf("\n\e[1;31mRELU \e[0m  \n");
  if (SIZE % VLEN == 0) {
    int *output_serial = new int[SIZE + VLEN];
    int *output_vector = new int[SIZE + VLEN];
    for (int i = 0; i < SIZE + VLEN; i++) {
      output_serial[i] = 514703087;
      output_vector[i] = 514703087;
    }

    ReluSerial(input_data, output_serial, SIZE);


    printf("\e[1;31mRelu Serial \e[0m  \n");
    bool result_serial = verifyint(input_data, output_serial, gold, SIZE);

    if (!result_serial) {
      printf("@@@ Failed!!!\n");
      return 1;
    } else {
      printf("Passed!!!\n");
    }

    ReluVector(input_data, output_vector, SIZE);
    printf("\e[1;31mRelu Vector \e[0m  \n");
    bool result_vector = verifyint(input_data, output_vector, gold, SIZE);
    if (printLog) {
      cs295Logger.printLog();
      cs295Logger.printStats();
    }
    if (!result_vector) {
      printf("@@@ Failed!!!\n");
      return 1;
    } else {
      printf("Passed!!!\n");
      return 0;
    }
  } else {
    printf(
        "SIZE must be multiple of VLEN for this problem (VLEN "
        "is %d)\n",
        VLEN);
    return 1;
  }
}

void usage(const char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Program Options:\n");
  printf("  -l  --log          Print vector unit execution log\n");
  printf("  -?  --help         This message\n");
}
