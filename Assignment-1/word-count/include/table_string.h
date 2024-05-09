#ifndef table_string_H
#define table_string_H
#define LINE_COUNT

#include "vector_string.h"
#include <stdbool.h>

// Struct describing the data structure table_string
// head* points to the entry which is the start of vector string
typedef struct table_string {
  vs_entry_t **heads; // Array to maintain the heads of each bucket.
  int buckets;        // Buckets can only be a power of 2.
} table_string;

/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
table_string *table_string_allocate(unsigned int buckets);

/**
 * @brief function that returns a value between 1
 */
unsigned int djb2_word_to_bucket(char *key, int buckets);

/**
 * @brief If word does not exist, Insert the string pointed to by key into the
 * table string If word exists, then simply increment the count in vs_entry_t
 *
 * @param vs - Pointer to table_string datastructure
 * @param key - Pointer to string to search for
 * @return * .
 */
void table_string_insert_or_add(table_string *vs, char *word, int line);
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to table_string struct
 */
void table_string_deallocate(table_string *vs);

/**
 * @brief Print all value in each entry of the vector string, one line at a time
 * [hello]
 * [world]
 * @param vs
 */
void table_string_print(table_string *vs);
#endif
