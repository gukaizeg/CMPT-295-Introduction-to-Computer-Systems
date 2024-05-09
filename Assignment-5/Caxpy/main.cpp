#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "Caxpy.h"
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

  int *backup_Y = (int*)malloc((SIZE + VLEN) * sizeof(int));
  memcpy(backup_Y, input_data_Y, (SIZE + VLEN) * sizeof(int));

  printf("\n\e[1;31mCAXPY Serial \e[0m  \n");


 CAXPYSerial(SIZE, conditions, input_data_a, input_data_X, input_data_Y);

 bool result_serial = verifyint(input_data_Y, input_data_Y, gold_data, SIZE);

  if (!result_serial) {
    printf("@@@ Failed!!!\n");
    return 1;
  } else {
    printf("Passed!!!\n");
  }

// Restore Y since its overwritten
  memcpy(input_data_Y, backup_Y, (SIZE + VLEN) * sizeof(int));

  CAXPYVector(SIZE, conditions, input_data_a, input_data_X, input_data_Y);

  if (printLog) {
    cs295Logger.printLog();
    cs295Logger.printStats();
  }

  printf("\e[1;31mCAXPY Vector \e[0m  \n");
  bool result_vector = verifyint(input_data_Y, input_data_Y, gold_data, SIZE);

  if (!result_vector) {
    printf("@@@ Failed!!!\n");
    return 1;
  } else {
    printf("Passed!!!\n");
    return 0;
  }
}

void usage(const char *progname) {
  printf("Usage: %s [options]\n", progname);
  printf("Program Options:\n");
  printf("  -l  --log          Print vector unit execution log\n");
  printf("  -?  --help         This message\n");
}
