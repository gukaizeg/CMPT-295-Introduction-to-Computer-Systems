#ifndef CHAR_VECTOR_H
#define CHAR_VECTOR_H

#include <stdint.h>
#include <stdlib.h>

struct vector_char {
  uint32_t len;
  uint32_t max;
  char *data;
};

// Gives name to struct so that you can declare variables
typedef struct vector_char vector_char_t;

extern vector_char_t *vector_char_allocate(void);

extern void vector_char_delete(vector_char_t *vector_char);

extern void vector_char_add(vector_char_t *vector_char, char entry);

extern char vector_char_get(vector_char_t *vector_char, uint32_t index);

extern char *vector_char_get_array(vector_char_t *vector_char);

#endif