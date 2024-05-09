#include "dogfault.h"
#include "cache.h"
#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// get the input from the file and call operateCache function to see if the
// address is in the cache.
void runTrace(char *traceFile, Cache *cache) {
  FILE *input = fopen(traceFile, "r");
  int size;
  char operation;
  result r;
  unsigned long long address;
  while (fscanf(input, " %c %llx,%d", &operation, &address, &size) == 3) {
    if (cache->displayTrace)
      printf("\n%c %llx,", operation, address);

    if (operation != 'M' && operation != 'L' && operation != 'S') {
      continue;
    }
    r = operateCache(address, cache);
    print_result(r);
    if (operation == 'M') { cache->hit_count++;}
    }
  fclose(input);
}


int main(int argc, char *argv[]) {
  Cache cache;
  cache.lfu = 0;
  opterr = 0;
  cache.displayTrace = 0;
  int option = 0;
  char *traceFile;
  // accepting command-line options
  // "assistance from"
  // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
  while ((option = getopt(argc, argv, "s:E:b:t:LFv")) != -1) {
    switch (option) {
    // select the number of set bits (i.e., use S = 2s sets)
    case 's':
      cache.setBits = atoi(optarg);
      break;
    // select the number of lines per set (associativity)
    case 'E':
      cache.linesPerSet = atoi(optarg);
      break;
    // select the number of block bits (i.e., use B = 2b bytes / block)
    case 'b':
      cache.blockBits = atoi(optarg);
      break;
    case 't':
      traceFile = optarg;
      break;
    case 'v':
      cache.displayTrace = 1;
      break;
    case 'L':
      cache.lfu = 0;
      break;
    case 'F':
      cache.lfu = 1;
      break;
    case 'h':
    default:
      printf("Usage: \n\
      ./ cache [-hv] - s<num> -E<num> -b<num> -t<file> (-L | -F) \n\
      Options : \n\
          -h Print this help message. \n\
          -v Optional verbose flag. \n\
          -s<num> Number of set index bits. \n\
          -E<num> Number of lines per set. \n\
          -b<num> Number of block offset bits. \n\
          -t<file> Trace file. \n\
          -L Use LRU eviction policy.- \n\
          -F Use LFU eviction poilcy\n");
      exit(1);
    }
  }
  // initializes the cache
  cacheSetUp(&cache, "L1");
  // check the flag and call appropriate function
  runTrace(traceFile, &cache);
  // prints the summary
  printSummary(&cache);
  //printSummary(cache.hit_count, cache.miss_count, cache.eviction_count);
  // deallocates the memory
  deallocate(&cache);
  return 0;
}
