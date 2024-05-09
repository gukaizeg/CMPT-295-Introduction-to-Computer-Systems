#ifndef CACHE_H
#define CACHE_H

#include "dogfault.h"
#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum status_enum {
  CACHE_MISS = 0,
  CACHE_HIT = 1,
  CACHE_EVICT = 2
};

typedef struct Line {
  unsigned long long block_addr;
  short valid;
  unsigned long long tag;
  // holds the place in used lines
  // the greater the rate, that much recent it is
  int r_rate;
} Line;

typedef struct Set {
  Line *lines;
  int recentRate;
  int placementRate;
} Set;

typedef struct Cache {
  int setBits;
  int linesPerSet;
  int blockBits;
  Set *sets;
  int eviction_count;
  int hit_count;
  int miss_count;
  short displayTrace;
  int lfu; // 0: Least Recently Used   1: Least Frequently Used.
  char* name; 
} Cache;

typedef struct result {
  int status;                    // 0: miss 1: hit 2: evict
  unsigned long long victim_block; // block address of the victime line.
  unsigned long long insert_block; // block address of inserted line.
} result;

void print_result(result r);

unsigned long long address_to_block(unsigned long long address,
                                    const Cache *cache);
unsigned long long cache_tag(const unsigned long long address,
                             const Cache *cache);

unsigned long long cache_set(const unsigned long long address,
                             const Cache *cache);

// Access address in cache. Called only if probe is successful.
// Update the LRU (least recently used) or MFU (most frequently used) counters.
void access_cache(const unsigned long long address, const Cache *cache);

// Check if the address is found in the cache.
// If so, return true, else return false.
bool probe_cache(const unsigned long long address, const Cache *cache);
// Check if the address is found in the cache. If so, return -1
// If not, then check if there is an empty spot. If so, place the address there
// and return 2 If there is no empty spot, then return -2
void allocate_cache(const unsigned long long address, const Cache *cache);


bool avail_cache(const unsigned long long address, const Cache *cache);

// if policy is 0, then it is LRU
// evict based on evict policy
unsigned long long victim_cache(const unsigned long long address,
                                Cache *cache);

// if policy is 0, then it is LRU
// evict based on evict policy
void evict_cache(const unsigned long long address, int index, Cache *cache);

// Evict block from cache. Need to find corresponding set and index.
// Block addresses have bottom blockBits bits set to 0.
// Essentially block_addr = tag << (setBits + blockBits)
void flush_cache(const unsigned long long block_addr, Cache *cache);

// checks if the address is in the cache, if not and if the cache is full
// evicts an address
result operateCache(const unsigned long long address, Cache *cache);

// initialize the cache
void cacheSetUp(Cache *cache, char *name);

// deallocate memory
void deallocate(Cache *cache);

void printSummary(const Cache *cache);
#endif // CACHE_H