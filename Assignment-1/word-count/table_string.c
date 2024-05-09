#include "table_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUCKETS
// DO NOT ADD ANY NEW FUNCTIONS BEFORE djb2
// Hash a character array to integer value between 0 and buckets-1.
// See here for more details: https://theartincode.stanis.me/008-djb2/
unsigned int djb2_word_to_bucket(char* word, int buckets)
{
    if (!word)
    {
        printf("Invoked with null string");
        exit(EXIT_FAILURE);
    }
    unsigned long hash = 5381;
    uint32_t i;

    for (i = 0; word[i]; i++)
        hash = ((hash << 5) + hash) + word[i];

    return hash & (buckets - 1);
}
// ADD YOUR HELPER FUNCTIONS AFTER djb2
/**
 * @brief Instantiate a table string
 *
 * @param buckets
 * @return table_string*
 */
table_string* table_string_allocate(unsigned int buckets)
{
    // Instantiate a bucket number of heads
    table_string* ts = (table_string*)malloc(sizeof(table_string));
    assert(ts);

    ts->buckets = buckets;
    ts->heads = (vs_entry_t**)malloc(sizeof(vs_entry_t*) * buckets);
    assert(ts->heads);
    unsigned int i;
    for (i = 0; i < buckets; i++)
    {
        ts->heads[i] = NULL;
    }


    return ts;
}

/**
 * @brief Insert the string pointed to by word into the table string.
 *   If word is already found increment count.
 *   If word is not found insert at the end of the corresponding bucket
 * @param ts - Pointer to table_string datastructure
 * @param word - Pointer to string to search for
 * @return * Find*
 */
void table_string_insert_or_add(table_string* ts, char* word, int line)
{
    // Find the bucket for word. djb2 will return a value between 0-buckets-1.
    // Rule: buckets can only be power of 2.
    int bucket = djb2_word_to_bucket(word, ts->buckets);
    // TODO:
    // Case head == NULL: bucket hasn't been initialized yet
    // Case word already in list, add to line array.
    // Case word not found, insert word and return.
    assert(ts);

    vs_entry_t dummy;
    vs_entry_t*cur, * head = &dummy;
    dummy.next = ts->heads[bucket];

    for (cur = head; cur->next; cur = cur->next)
    {
        if (my_str_cmp(cur->next->value, word) == 0)
        {
            break;
        }
    }
    if (cur->next == NULL)
    {
        // cannot found
        cur->next = (struct vs_entry*)malloc(sizeof(struct vs_entry));
        assert(cur->next);
        cur->next->value = word;
        cur->next->next = NULL;
        cur->next->size_of_lines = 0;
        cur->next->lines = NULL;
    }
    else
    {
        free(word);
    }
    cur->next->lines = (int *)realloc(cur->next->lines, (cur->next->size_of_lines + 1) * sizeof(int));
    assert(cur->next->lines);
    cur->next->lines[cur->next->size_of_lines] = line;
    cur->next->size_of_lines++;

    ts->heads[bucket] = dummy.next;
}

void table_string_deallocate(table_string* ts)
{
    // TODO:
    // Free the linked list of each bucket
    // Free the array of head pointers
    // Free the structure itself
    unsigned int i;
    for (i = 0; i <ts-> buckets; i++)
    {
        vs_entry_t* head = ts->heads[i], * next;
        while (head)
        {
            next = head->next;
            free(head->value);
            free(head->lines);
            free(head);
            head = next;
        }
    }
    free(ts->heads);
    free(ts);

    return;
}

void table_string_print(table_string* ts)
{
    /** TODO:
     for each bucket
      for each entry in bucket
        print entry->word: line line line
    */
    unsigned int i;
    for (i = 0; i < ts->buckets; i++)
    {
        vs_entry_t* cur;
        for (cur = ts->heads[i]; cur; cur = cur->next)
        {
            printf("%s: ", cur->value);
            int j;
            for (j = 0; j < cur->size_of_lines; j++)
            {
                printf("%d ", cur->lines[j]);
            }
            printf("\n");
        }
    }
}
