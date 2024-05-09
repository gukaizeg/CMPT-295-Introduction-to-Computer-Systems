#include <stdio.h>
#include <algorithm>
#include <getopt.h>
#include <math.h>
#include "intrin.h"
#include "logger.h"
#include "helpers.h"
#include "dataset.h"
#include "SoA.h"

using namespace std;

int SoASerial(int *values, int N);
int SoAVector(int *values, int N);

#define EXP_MAX 1024

Logger cs295Logger;

void usage(const char *progname);
void initValue(int *values, int *exponents, int *output, int *gold, unsigned int N);
bool verifyResult(int *values, int *exponents, int *output, int *gold, int N);

int main(int argc, char *argv[])
{
  bool printLog = false;

  // parse commandline options ////////////////////////////////////////////
  int opt;
  static struct option long_options[] = {
      {"log", 0, 0, 'l'},
      {"help", 0, 0, '?'},
      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "s:l?", long_options, NULL)) != EOF)
  {
    switch (opt)
    {
    case 'l':
      printLog = true;
      break;
    case '?':
    default:
      usage(argv[0]);
      return 1;
    }
  }
  
  printf("\n\e[1;31mARRAY SUM\e[0m (bonus) \n");
  if (SIZE % VLEN == 0)
  {
    int sumGold = SoASerial(input_data, SIZE);
    int sumOutput = SoAVector(input_data, SIZE);
    float epsilon = SIZE * 1e-4;
    bool sumCorrect = abs(sumGold - sumOutput) < (epsilon * 2);

    if (printLog) {
      cs295Logger.printLog();
      cs295Logger.printStats();
    }
    
    if (!sumCorrect)
    {
      printf("Expected %d, got %d\n.", sumGold, sumOutput);
      printf("@@@ Failed!!!\n");
      return 1;
    }
    else
    {
      printf("Passed!!!\n");
      return 0;
    }
  }
  else
  {
    printf("SIZE must be multiple of VLEN for this problem (VLEN is %d)\n", VLEN);
    return 1;  
  }

}

void usage(const char *progname)
{
  printf("Usage: %s [options]\n", progname);
  printf("Program Options:\n");
  printf("  -l  --log          Print vector unit execution log\n");
  printf("  -?  --help         This message\n");
}



