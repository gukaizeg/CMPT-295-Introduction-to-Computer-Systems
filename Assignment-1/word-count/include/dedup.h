#ifndef DEDUP_H
#define DEDUP_H

#include <stdbool.h>
#include "table_string.h"

typedef struct dedup_entry {
  char *value; // Word
  char *file1; // Filename of the first file
  int* lines1; // Array for holding lines of file1
  char *file2; // Filename of the second file
  int* lines2; // Array for holding lines of file2
  int size_of_lines1; // Size of lines1
  int size_of_lines2; // Size of lines2
} dedup_entry_t;


/**
 * @brief Find duplicate words between file 1 and file 2
 * 
 * @param t1 : Table string of file1
 * @param f1 : File name of file1
 * @param t2 : Table string of file2
 * @param f2 : File name of file2
 * @return int : Number of duplicate words
 */ 

int dedup(table_string *t1, char* f1, table_string *t2, char* f2);

#endif // DEDUP_H