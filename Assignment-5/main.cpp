p#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
using namespace std;

extern void absSerial(float *values, float *output, int N);
extern void absVector(float *values, float *output, int N);
extern void clampedExpSerial(float *values, int *exponents, float *output,
                             int N);
extern void clampedExpVector(float *values, int *exponents, float *output,
                             int N);
extern float arraySumSerial(float *values, int N);
extern float arraySumVector(float *values, int N);

#define EXP_MAX 1024

Logger cs295Logger;

void usage(const char *progname);
void initValue(float *values, int *exponents, float *output, float *gold,
               unsigned int N);
void absSerial(float *values, float *output, int N);
void absVector(float *values, float *output, int N);
void clampedExpSerial(float *values, int *exponents, float *output, int N);
void clampedExpVector(float *values, int *exponents, float *output, int N);
float arraySumSerial(float *values, int N);
float arraySumVector(float *values, int N);
bool verifyfloat(float *values, int *exponents, float *output, float *gold,
                 int N);

int main(int argc, char *argv[]) {
  int N = 16;
  bool printLog = false;

  // parse commandline options ////////////////////////////////////////////
  int opt;
  static struct option long_options[] = {{"size", 1, 0, 's'},
                                         {"log", 0, 0, 'l'},
                                         {"help", 0, 0, '?'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "s:l?", long_options, NULL)) != EOF) {

    switch (opt) {
    case 's':
      N = atoi(optarg);
      if (N <= 0) {
        printf("Error: Workload size is set to %d (<0).\n", N);
        return -1;
      }
      break;
    case 'l':
      printLog = true;
      break;
    case '?':
    default:
      usage(argv[0]);
      return 1;
    }
  }
  
  // Initialize Floating Inputs
  float *values = new float[N + VLEN];
  int *exponents = new int[N + VLEN];
  float *output = new float[N + VLEN];
  float *gold = new float[N + VLEN];
  initValue(values, exponents, output, gold, N);

  absSerial(values, gold, N);
  absVector(values, output, N);

  printf("\e[1;31mAbsolute \e[0m (required) \n");
  bool absCorrect = verifyfloat(values, exponents, output, gold, N);
  if (printLog)
    cs295Logger.printLog();
  cs295Logger.printStats();

  clampedExpSerial(values, exponents, gold, N);
  clampedExpVector(values, exponents, output, N);

  printf("\e[1;31mCLAMPED EXPONENT\e[0m (required) \n");
  bool clampedCorrect = verifyfloat(values, exponents, output, gold, N);
  if (printLog)
    cs295Logger.printLog();
  cs295Logger.printStats();

  printf("\n\e[1;31mARRAY SUM\e[0m (bonus) \n");
  if (N % VLEN == 0) {
    float sumGold = arraySumSerial(values, N);
    float sumOutput = arraySumVector(values, N);
    float epsilon = N * 1e-4;
    bool sumCorrect = abs(sumGold - sumOutput) < epsilon * 2;
    if (!sumCorrect) {
      printf("Expected %f, got %f\n.", sumGold, sumOutput);
      printf("@@@ Failed!!!\n");
    } else {
      printf("Passed!!!\n");
    }
  } else {
    printf("Must have N % VLEN == 0 for this problem (VLEN is "
           "%d)\n",
           VLEN);
  }

  delete[] values;
  delete[] exponents;
  delete[] output;
  delete gold;

  printf("************************ Result Verification "
         "*************************\n");
  if (!clampedCorrect) {
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
  printf("  -s  --size <N>     Use workload size N (Default = 16)\n");
  printf("  -l  --log          Print vector unit execution log\n");
  printf("  -?  --help         This message\n");
}

