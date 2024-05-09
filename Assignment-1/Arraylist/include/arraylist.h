
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct arraylist
{
    void **buffer;            // pointer to allocated memory
    unsigned int buffer_size; // the max number of elements the buffer can hold
    unsigned int length;      // the number of integers stored in the list
} arraylist;

////////////////////////////////////////////////////////////////////////////////
/*
 * Append the value x to the end of the arraylist. If necessary, double the
 * capacity of the arraylist.
 */
void arraylist_add(arraylist *a, void *x);

/*
 * Store x at the specified index of the arraylist. Previously stored values
 * should be moved back rather than overwritten. It is undefined behavior to
 * insert an element with an index beyond the end of an arraylist.
 */
void arraylist_insert(arraylist *a, unsigned int index, void *x);

/*
 * Free any memory used by that arraylist.
 */
void arraylist_free(arraylist *a);
////////////////////////////////////////////////////////////////////////////////

arraylist *arraylist_new();

void arraylist_remove(arraylist *a, unsigned int index);

void *arraylist_get(arraylist *a, unsigned int index);
void arraylist_print(arraylist *a);
void arraylist_output(arraylist *a, char *output, int *pos);