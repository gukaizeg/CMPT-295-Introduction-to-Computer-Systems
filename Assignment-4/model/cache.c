#include "cache.h"
#include "dogfault.h"
#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// DO NOT MODIFY THIS FILE. INVOKE AFTER EACH ACCESS FROM runTrace
void print_result(result r)
{
    if (r.status == CACHE_EVICT)
        printf(" [status: %d victim_block: 0x%llx insert_block: 0x%llx]", r.status,
            r.victim_block, r.insert_block);
    if (r.status == CACHE_HIT)
        printf(" [status: %d]", r.status);
    if (r.status == CACHE_MISS)
        printf(" [status: %d insert_block: 0x%llx]", r.status, r.insert_block);
}

// HELPER FUNCTIONS USEFUL FOR IMPLEMENTING THE CACHE
// Convert address to block address. 0s out the bottom block bits.
unsigned long long address_to_block(const unsigned long long address,
    const Cache* cache)
{
    unsigned long long block = address & ((1 << cache->blockBits) - 1);
    return block;
}

// Access the cache. If the address is found in the cache, return true. else return false.
void access_cache(const unsigned long long address, const Cache* cache)
{
    unsigned long long tag = cache_tag(address, cache);
    unsigned long long set = cache_set(address, cache);
    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[i].valid
            && cache->sets[set].lines[i].tag == tag)
        {
            return;
        }
    }
}

// Calculate the tag of the address. 0s out the bottom set bits and the bottom block bits.
unsigned long long cache_tag(const unsigned long long address,
    const Cache* cache)
{
    unsigned long long tag;
    tag = address >> (cache->blockBits + cache->setBits);
    return tag;
}

// Calculate the set of the address. 0s out the bottom block bits, 0s out the tag bits, and then shift the set bits to the right.
unsigned long long cache_set(const unsigned long long address,
    const Cache* cache)
{
    unsigned long long set;
    set = (address >> cache->blockBits) & ((1 << cache->setBits) - 1);
    return set;
}

// Check if the address is found in the cache. If so, return true. else return false.
bool probe_cache(const unsigned long long address, const Cache* cache)
{
    unsigned long long tag = cache_tag(address, cache);
    unsigned long long set = cache_set(address, cache);
    // unsigned long long block = address_to_block(address, cache);
    //
    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[i].valid
            && cache->sets[set].lines[i].tag == tag)
        {
            return true;
        }
    }
    return false;
}

// Allocate an entry for the address. If the cache is full, evict an entry to create space. This method will not fail. When method runs there should have already been space created. 
void allocate_cache(const unsigned long long address, const Cache* cache)
{
}

// Is there space available in the set corresponding to the address?
bool avail_cache(const unsigned long long address, const Cache* cache)
{
    unsigned long long set = cache_set(address, cache);
    // calculate tag and set values
    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[i].valid == 0)
        {
            return true;
        }
    }
    return false;
}

// If the cache is full, evict an entry to create space. This method figures out which entry to evict. Depends on the policy.
unsigned long long victim_cache(const unsigned long long address,
    Cache* cache)
{
    unsigned long long set = cache_set(address, cache);
    int whichLine = 0;
    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[whichLine].r_rate > cache->sets[set].lines[i].r_rate)
        {
            whichLine = i;
        }
    }
    return whichLine;
}

// Set can be determined by the address. Way is determined by policy and set by the operate cache. 
void evict_cache(const unsigned long long address, int way, Cache* cache)
{
}

// Given a block address, find it in the cache and when found remove it.
// If not found don't remove it. Useful when implementing 2-level policies. 
// and triggering evictions from other caches. 
void flush_cache(const unsigned long long block_address, Cache* cache)
{
    unsigned long long tag = cache_tag(block_address, cache);
    unsigned long long set = cache_set(block_address, cache);

    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[i].tag == tag)
        {
            if (cache->sets[set].lines[i].valid)
            {
                cache->eviction_count++;
            }
            cache->sets[set].lines[i].valid = 0;
        }
    }
}
// checks if the address is in the cache, if not and if the cache is full
// evicts an address
result operateCache(const unsigned long long address, Cache* cache)
{
    static int TIMES = 0;
    TIMES++;
    // checkCache checks if the address is in the cache
    result r;

    unsigned long long tag = cache_tag(address, cache);
    unsigned long long set = cache_set(address, cache);
    // unsigned long long block = address_to_block(address, cache);

    int whichLine = -1;

    // address already in cache?
    for (int i = 0; i < cache->linesPerSet; i++)
    {
        if (cache->sets[set].lines[i].valid
            && cache->sets[set].lines[i].tag == tag)
        {

            whichLine = i;
            r.status = CACHE_HIT;
            break;
        }
    }
    if (whichLine == -1)
    {
        // find an empty line
        for (int i = 0; i < cache->linesPerSet; i++)
        {
            if (cache->sets[set].lines[i].valid == 0)
            {
                whichLine = i;
                r.status = CACHE_MISS;
                r.insert_block = (tag << (cache->setBits + cache->blockBits)) + (set << (cache->blockBits));
                break;
            }
        }
    }
    if (whichLine == -1)
    {
        // find a victim
        whichLine = 0;
        for (int i = 0; i < cache->linesPerSet; i++)
        {
            assert(cache->sets[set].lines[i].valid == 1);
            assert(whichLine == 0 || cache->sets[set].lines[whichLine].r_rate != cache->sets[set].lines[i].r_rate);
            if (cache->sets[set].lines[whichLine].r_rate > cache->sets[set].lines[i].r_rate)
            {
                whichLine = i;
            }
        }
        r.status = CACHE_EVICT;
        r.victim_block = cache->sets[set].lines[whichLine].block_addr;
        r.insert_block = (tag << (cache->setBits + cache->blockBits)) + (set << (cache->blockBits));
    }
    cache->sets[set].lines[whichLine].r_rate = TIMES;
    cache->sets[set].lines[whichLine].tag = tag;
    cache->sets[set].lines[whichLine].valid = 1;
    cache->sets[set].lines[whichLine].block_addr = (tag << (cache->setBits + cache->blockBits)) + (set << (cache->blockBits));

    if (r.status == CACHE_HIT)
    {
        cache->hit_count++;
        if (cache->displayTrace)
        {
            printf(" %s hit ", cache->name);
        }

    }
    else if (r.status == CACHE_MISS)
    {
        cache->miss_count++;
        if (cache->displayTrace)
        {
            printf(" %s miss ", cache->name);
        }
    }
    else
    {
        cache->miss_count++;
        cache->eviction_count++;
        if (cache->displayTrace)
        {
            printf(" %s miss eviction ", cache->name);
        }
    }
    return r;
}

// initialize the cache and allocate space for it
void cacheSetUp(Cache* cache, char* name)
{
    //int eviction_count;
    //int hit_count;
    //int miss_count;
    cache->eviction_count = 0;
    cache->hit_count = 0;
    cache->miss_count = 0;
    cache->name = name;
    int totalSets = 1 << cache->setBits;

    cache->sets = (Set*)malloc(sizeof(Set) * totalSets);
    for (int i = 0; i < totalSets; i++)
    {
        cache->sets[i].lines = (Line*)malloc(sizeof(Line) * cache->linesPerSet);
        cache->sets[i].placementRate = 0;
        cache->sets[i].recentRate = 0;
        for (int j = 0; j < cache->linesPerSet; j++)
        {
            cache->sets[i].lines[j].valid = 0;
            cache->sets[i].lines[j].r_rate = 42;
            cache->sets[i].lines[j].tag = 42;
        }
    }
}

// deallocate memory
void deallocate(Cache* cache)
{
    int totalSets = 1 << cache->setBits;
    for (int i = 0; i < totalSets; i++)
    {
        free(cache->sets[i].lines);
    }
    free(cache->sets);
}

void printSummary(const Cache* cache)
{
    printf("\n%s hits:%d misses:%d evictions:%d", cache->name, cache->hit_count,
        cache->miss_count, cache->eviction_count);
    // printf("\n");
}
