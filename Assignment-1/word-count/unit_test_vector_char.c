/* To build:
gcc -I ./include/ unit_test_vector_char.c lib/vector_char/vector_char.c
 */
#include "vector_char.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
int main() {
  vector_char_t *header = vector_char_allocate();

  // inserts "h" at the end of the vector
  vector_char_add(header, 'H');
  char ch = 'E';
  vector_char_add(header, ch);
  vector_char_add(header, 'L');
  vector_char_add(header, 'L');
  vector_char_add(header, 'O');
  vector_char_add(header, ' ');
  vector_char_add(header, 'W');
  vector_char_add(header, 'O');
  vector_char_add(header, 'R');
  vector_char_add(header, 'L');
  vector_char_add(header, 'D');
  // char array termination character. Need to enable easy printing
  vector_char_add(header, '\0');

  // Pointer to string on heap.
  // data_ptr on stack. Actual data on heap.
  char *data_ptr = vector_char_get_array(header);
  printf("Actual:%s \n", data_ptr);

  /**
   Transform all upper case to lower case using integer math.
    In Ascii upper case 'A' is encoded as integer value 65.
   In Ascii lower case 'a'  is encoded as 97
    To change upper to lower we simply need to add difference 32 to each upper
    case character. Subtract 32 to change lower to upper
  */
  char *cursor = data_ptr;
  /**
   * Iterating over array using a cursor until termination character is
   *reached
   **/
  while (*cursor != '\0') {
    // Dereference character under cursor. Check if character is [A-Z]
    // 'A' is 65 Z is '90'. All other upper case alpha between 65 and 90
    if (*cursor >= 65 && *cursor <= 90) {
      *cursor = *cursor + 32; // Change upper to lower
    }
    cursor++;
  }
  printf("Lower: %s \n", data_ptr);

  printf("Length (without \\0 termination character): %ld", strlen(data_ptr));
}
