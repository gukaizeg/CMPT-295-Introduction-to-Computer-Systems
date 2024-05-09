#include "vector_char.h"
#include <stdio.h>

/* Internal functions declared here . See bottom for definition */
static void _vector_char_expand(vector_char_t *vector_char);
static void _free(void *ptr);

/**
 * @brief Allocate header for describing vector chars. Initialize internal data
 * pointer to NULL
 *
 * @return vector_char_t*
 */
vector_char_t *vector_char_allocate(void) {

  vector_char_t *header = (vector_char_t *)malloc(sizeof(vector_char_t));
  if (!header)
    return NULL;

  header->data = NULL;
  header->len = header->max = 0;

  return header;
}

/**
 * @brief Clean up both the header describing vector_char and internal data
 *
 * @param vector_char
 */
void vector_char_delete(vector_char_t *vector_char) {
  if (!vector_char)
    return;

  if (vector_char->max)
    _free(vector_char->data);

  _free(vector_char);
}

void vector_char_add(vector_char_t *vector_char, char entry) {
  if (vector_char->len >= vector_char->max)
    _vector_char_expand(vector_char);

  vector_char->data[vector_char->len++] = entry;
}

/**
 * @brief Get the character at a particular location
 *
 * @param vector_char
 * @param index
 * @return char
 */
char vector_char_get(vector_char_t *vector_char, uint32_t index) {
  if (index > vector_char->len)
    exit(EXIT_FAILURE);

  return vector_char->data[index];
}

/**
 * @brief returns the internal char array as a raw pointer
 * WARNING: Do not free on the outside. This will lead to inconsistent results
 * @param vector_char
 * @return char*
 */
char *vector_char_get_array(vector_char_t *vector_char) {
  return vector_char->data;
}

/**
 * @brief Internal use only. User does not interact with these functions
 *
 */
static void _vector_char_expand(vector_char_t *vector_char) {
  if (!vector_char->max) {
    vector_char->max = 1;
    vector_char->data = malloc(vector_char->max * sizeof(char));
    if (!vector_char->data)
      exit(EXIT_FAILURE);
    return;
  }

  vector_char->max <<= 1;
  vector_char->data =
      realloc(vector_char->data, sizeof(char) * vector_char->max);
  if (!vector_char->data)
    exit(EXIT_FAILURE);
}

static void _free(void *ptr) {
  free(ptr);
  ptr = NULL;
}