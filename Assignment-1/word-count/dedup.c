#include "dedup.h"
#include "table_string.h"
#include "vector_char.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_cmp.h"

vs_entry_t* search_list(const char* word, vs_entry_t* head)
{
    while (head)
    {
        if (my_str_cmp(word, head->value) == 0)
        {
            break;
        }
        head = head->next;
    }
    return head;
}

int dedup(table_string* ts1, char* file1, table_string* ts2, char* file2)
{
    // Find common strings between ts1 and ts2
    // Store in array and print them
    // You can make use of dedup_entry_t (if you want; you can also ignore if you wish)
      // Print them.
      // printf("\n%s", word);
      // printf("\n%s ", file1);
      // Print all lines in file1 with word , separated
      // printf("%d,", entry[i].lines1[j]);
      // printf("\n%s", file2);
      // printf("%d,", entry[i].lines2[j]);

    int i,j ;
    for (i = 0; i < ts1->buckets; i++)
    {
        vs_entry_t* head1;
        for (head1 = ts1->heads[i]; head1; head1 = head1->next)
        {
            vs_entry_t* head2 = search_list(head1->value, ts2->heads[i]);
            if (head2)
            {
                printf("\n%s", head1->value);

                printf("\n%s ", file1);
                for (j = 0; j < head1->size_of_lines; j++)
                {
                    printf("%d,", head1->lines[j]);
                }
                printf("\n%s ", file2);
                for (j = 0; j < head2->size_of_lines; j++)
                {
                    printf("%d,", head2->lines[j]);
                }
            }
        }
    }
    return 0;
}


