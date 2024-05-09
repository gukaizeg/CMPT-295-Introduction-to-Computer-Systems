#ifndef vector_string_H
#define vector_string_H

#include <stdbool.h>

/**
A vector string is a list of strings. It should be implemented as a linked list
of strings, into which entries can be dynamically inserted.

1. vector_string describes the top level header of the data structure and
contains a pointer to the head and tail of the list. The head points to the
first entry in the list. tail points to the last entry in the list.


2. vs_entry describes each entry in the list and contains two fields i) value -
a pointer to a character array. This is meant to hold the word. and ii) next.
This points to the next entry in the list.


               Header
             +----------------------+                       -
          +---   vs_entry_t *head;  |
          |  |   vs_entry_t *tail;  | --------------------------
          |  +----------------------+                          |
          |                                                    | -
          |----+                                               |
               |                                               |
               |-----------+             +-----------+          +-----------+
               | next*     |------------+| next*     |----------- next*     |
               | value*    |             | value     |          | value     |
             + +-----------+             +-----------+          +-----------+
             |                                         -
             |--++---+---+---++---+
             |"h" "e" "l" "l" "o" |
             +--++---+---+---++---+
 *
 */

typedef struct vs_entry {
  char *value;
  struct vs_entry *next;

// Conditionally compiled in code. Not relevant for part 2. You can assume the
// int count declaration does not exist and is irrelevant for part 2.
#ifdef LINE_COUNT
  int* lines; // This keeps track of each line the word is found in
  int  size_of_lines; // This keeps size of lines. Remember in C we track array size explicitly.
#endif
} vs_entry_t;

// Struct describing the data structure vector_string
// head* points to the entry which is the start of vector string
typedef struct vector_string {
  vs_entry_t *head;
  vs_entry_t *tail;
} vector_string;

/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string *vector_string_allocate();

/**
 * @brief Search the vector string pointed to by vs and return the entry if the
 * vs_entry.value == key.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
bool vector_string_find(vector_string *vs, char *key);

/**
 * @brief Insert the string pointed to by key into the vector string.
 *  TODO: char* is externally allocated. You do not have to allocate internally
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string *vs, char *key);
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string *vs);

/**
 * @brief Print all value in each entry of the vector string, one line at a time
 * [hello]
 * [world]
 * @param vs
 */
void vector_string_print(vector_string *vs);
#endif