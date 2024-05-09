#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table_string.h>
#include <vector_char.h>


int is_alpha(char c)
{
    return ('a' <= c && c <= 'z')
        || ('A' <= c && c <= 'Z')
        || ('0' <= c && c <= '9');
}

int my_str_len(const char* s)
{
    int i = 0;
    while (s[i])
    {
        i++;
    }
    return i;
}

void my_str_cpy(char* dst, const char* src)
{
    int i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = 0;
}

char* my_str_dup(const char* s)
{
    char* r = (char*)malloc(my_str_len(s) + 1);
    my_str_cpy(r, s);
    return r;
}


int main(int argc, char** argv)
{
    char* source = NULL;

    if (argc != 2)
    {
        printf("./wordcount.bin [FILE PATH]");
        exit(1);
    }
    /**
     * @brief Read file into source.
     * source is a character array with file contents
     * It is null terminated
     */
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL)
    { /* Error */
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

    /** Start processing file and separate into words */
    // TODO: Write linecount

    table_string* ts = table_string_allocate(4);

    int line = 1;
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
            vector_char_t* vec = vector_char_allocate();
            for (j = begin; j < i; j++)
            {
                vector_char_add(vec, source[j]);
            }
            vector_char_add(vec, '\0');

            char* word = my_str_dup(vector_char_get_array(vec));
            table_string_insert_or_add(ts,   word,   line);

            vector_char_delete(vec);
        }
        
        if (source[i] == '\n')
        {
            line++;
        }
        if (source[i] == 0)
        {
            break;
        }
        i++;
    }
    free(source);

    table_string_print(ts);
    table_string_deallocate(ts);

    return 0;
}