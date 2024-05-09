#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct hash_bucket hash_bucket_t;
typedef struct hash_table  hash_table_t;

typedef uint32_t (*hash_fn_t)(void *key, size_t key_len);
typedef size_t 	 (*key_len_fn_t)(void *key);

extern hash_table_t *hash_table_constructor(uint32_t size, hash_fn_t hash_fn, key_len_fn_t key_len_fn);

extern void hash_table_destructor(hash_table_t *hash_table);

extern void *hash_table_find(hash_table_t *hash_table, void *key);

extern void hash_table_insert(hash_table_t *hash_table, void *key, void *val);

extern void hash_table_delete(hash_table_t *hash_table, void *key);

#endif