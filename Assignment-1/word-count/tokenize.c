#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector_char.h>


int is_alpha(char c)
{
    return ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z')
        || ('0' <= c && c <= '9');
}

int main(int argc, char** argv)
{
    char* source = NULL;

    /**
     * @brief Read file into source.
     * source is a character array with file contents
     * It is null terminated
     */
    if (argc != 2)
    {
        printf("./grade_tokenize.bin [FILE PATH] \n");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        /* Error */
        printf("Error reading file");
        exit(1);
    }
    if (fp != NULL)
    {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0)
        {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1)
            { /* Error */
                printf("Error reading file");
            }
            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));
            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0)
            { /* Error */
            }
            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if (ferror(fp) != 0)
            {
                printf("Error reading file");
            }
            else
            {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
    }
    fclose(fp);

    // TODO: Tokenize processing
    // TODO:source contains the string to be processed.
    /** Start processing file and separate into words */
    /** Pseudocode */
    // 1. Iterate over characters
    // 2. if current-character starts word start accumulating into vector_char
    // 3. if current character terminates word. print and restart word start
    // check. Free all data.
    // Hint: Use vector_char

    int begin = 0;
    int i = 0, j;
    while (1)
    {
        // if current-character starts word start accumulating into vector_char
        if ((i == 0 || !is_alpha(source[i - 1])) && is_alpha(source[i]))
        {
            begin = i;
        }
        else if (i > 0 && is_alpha(source[i - 1]) && !is_alpha(source[i]))
        {
            vector_char_t* vec= vector_char_allocate( );
            for (j = begin; j < i; j++)
            {
                vector_char_add(vec, source[j]);
            }
            vector_char_add(vec, '\0');
            printf("%s\n", vector_char_get_array(vec));
            vector_char_delete(vec);
        }
        if (source[i] == 0)
        {
            break;
        }
        i++;
    }
    free(source);
    return 0;
}