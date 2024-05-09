#include "cache.h"
#include "dogfault.h"
#include "fileio.h"
#include "json.h"
#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Validate 2 level correctness. Every block in L1 cache also exists in L2
// cache. Blocks in L2 cache may not exist in L1 cache.
void validate_2level(const Cache *L1, const Cache *L2) {
  for (int i = 0; i < (1 << L1->setBits); i++)
    for (int j = 0; j < L1->linesPerSet; j++)
      if (L1->sets[i].lines[j].valid)
        assert(probe_cache(L1->sets[i].lines[j].block_addr, L2) &&
               "Inclusive Property Violation: L1 Cache Block not found in L2 "
               "Cache.");
}
// get the input from the file and call operateCache function to see if the
// address is in the cache.
void runTrace(char *traceFile, Cache *L1, Cache *L2) {
  FILE *input = fopen(traceFile, "r");
  int size;
  char operation;
  unsigned long long address;
  result r_L1, r_L2;
  while (fscanf(input, " %c %llx,%d", &operation, &address, &size) == 3) {
    printf("\n%c %llx,", operation, address);

    if (operation != 'M' && operation != 'L' && operation != 'S') {
      continue;
    }

    // TODO: Operate L1 and L2 cache to implement
    // 2-level inclusive cache model
    /*
   Access   L1 Hit
      │      ▲
      │      │
  ┌───▼──────┴───┐
  │              │
  │   L1 Cache   │
  │              │
  └───┬──────▲───┘
      │      │
      │      │
L1 Miss      │L2 Hit
      │      │
   ┌──▼──────┴───┐
   │             │
   │  L2 Cache   │
   |             │
   └────────┬────┘
            │
            │L2 miss
            ▼
 */
    // Operate L1 cache first.
    // If miss, operate L2 cache
    // Consider evictions in L1 and L2. What would happen if block evicted from
    // L1 or L2. Under all circumstances, you should ensure that the blocks in
    // L1, also exist in L2.

        r_L1 = operateCache(address, L1);
        print_result(r_L1);

        // If miss, operate L2 cache
        if (r_L1.status == CACHE_EVICT || r_L1.status == CACHE_MISS)
        {
            r_L2 = operateCache(address, L2);
            print_result(r_L2);
            flush_cache(r_L2.victim_block, L1);
        }


    if (operation == 'M') {
      L1->hit_count++;
    }
    validate_2level(L1, L2);
  }
  fclose(input);
}

int main(int argc, char *argv[]) {
  char *configFile = "2-level.config";
  char *traceFile = "example.trace";
  int option = 0;
  int lfu = 0;
  while ((option = getopt(argc, argv, "c:t:h:LF")) != -1) {
    switch (option) {
    case 't':
      traceFile = optarg;
      break;
    case 'L':
      lfu = 0;
      break;
    case 'F':
      lfu = 1;
      break;
    case 'c':
      configFile = optarg;
      break;
    case 'h':
    default:
      printf("Usage: \n\
      ./ cache [-h] -c<file> -t<file> (-L | -F) \n\
      Options : \n\
          -h Print this help message. \n\
          -t<file> Trace file. \n\
          -c<file> Configuration file. \n\
          -L Use LRU eviction policy.\n\
          -F Use LFU eviction poilcy\n");
      exit(1);
    }
  }

  // Parse Cache config. YOU DO NOT NEED TO READ THIS CODE
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  char *payload = readfile(configFile);
  struct json_value_s *const value = json_parse(payload, strlen(payload));
  struct json_object_s *object = (struct json_object_s *)value->payload;
  struct json_number_s *field =
      (struct json_number_s *)object->start->value->payload;
  int L1_setBits = strtol(field->number, NULL, 10);
  field = (struct json_number_s *)object->start->next->value->payload;
  int L1_ways = strtol(field->number, NULL, 10);
  field = (struct json_number_s *)object->start->next->next->value->payload;
  int blockBits = strtol(field->number, NULL, 10);
  field =
      (struct json_number_s *)object->start->next->next->next->value->payload;
  int L2_setBits = strtol(field->number, NULL, 10);
  field = (struct json_number_s *)
              object->start->next->next->next->next->value->payload;
  int L2_ways = strtol(field->number, NULL, 10);

  //  See variables listed here. These are the ones you will be using for
  //  initializing your caches.
  // ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  printf("###### Configuration #########");
  printf("L1_setBits: %d\n", L1_setBits);
  printf("L1_ways: %d\n", L1_ways);
  printf("L1 and L2 blockBits: %d\n", blockBits);
  printf("L2_setBits: %d\n", L2_setBits);
  printf("L2_ways: %d\n", L2_ways);
  printf("############################\n");
  // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  opterr = 0;
  Cache L1;
  L1.lfu = lfu;
  L1.displayTrace = 1;
  // TODO: Initialize L1 cache
    L1.setBits = L1_setBits;
    L1.linesPerSet = L1_ways;
    L1.blockBits = blockBits;
    L1.displayTrace = 1;
    cacheSetUp(&L1, "L1");


  Cache L2;
  L2.lfu = lfu;
  L2.displayTrace = 1;
  // TODO: Initialize L2 cache

    L2.setBits = L2_setBits;
    L2.linesPerSet = L2_ways;
    L2.blockBits = blockBits;
    L2.displayTrace = 1;
    cacheSetUp(&L2, "L2");

  runTrace(traceFile, &L1, &L2);

  printSummary(&L1);
  printSummary(&L2);
  return 0;
}
