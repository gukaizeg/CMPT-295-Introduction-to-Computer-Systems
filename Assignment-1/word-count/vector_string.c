#include "vector_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/**
/////////////////////////////////////////

*/
/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string* vector_string_allocate()
{
    vector_string* vec = (vector_string*)malloc(sizeof(vector_string));
    assert(vec);
    vec->head = NULL;
    vec->tail = NULL;
    return vec;
}

/**
 * @brief Search the vector string pointed to by vs and return true if the
 * vs_entry.value == key, else return false.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
bool vector_string_find(vector_string* vs, char* key)
{
    vs_entry_t* entry;
    for (entry = vs->head; entry; entry = entry->next)
    {
        if (my_str_cmp(entry->value, key) == 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief TODO: Insert the string pointed to by key into the vector string.
 *  char* is externally allocated. You do not have to allocate internally
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string* vs, char* key)
{
    // Insert the string into the tail of the list.

    vs_entry_t* entry = (vs_entry_t*)malloc(sizeof(vs_entry_t));
    assert(entry);
    entry->value = key;
    entry->next = NULL;

    assert(vs);
    if (vs->head == NULL)
    {
        vs->head = entry;
        vs->tail = entry;
    }
    else
    {
        vs->tail->next = entry;
        vs->tail = entry;
    }
}
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string* vs)
{
    assert(vs);

    vs_entry_t* entry = vs->head, * next;
    while (entry)
    {
        next = entry->next;
        free(entry->value);
        free(entry);
        entry = next;
    }
    free(vs);
}

/**
 * @brief Print all value in each entry of the vector string, in the following
 * format. In this case hello and world are the unique words in the file.
 * 1. hello
 * 2. world
 * @param vs
 */
void vector_string_print(vector_string* vs)
{

    //printf("%d. %s\n", count, entry->value);
    vs_entry_t* entry;
    int count = 1;
    for (entry = vs->head; entry; entry = entry->next)
    {
        printf("%d. %s\n", count, entry->value);
        count++;
    }
}