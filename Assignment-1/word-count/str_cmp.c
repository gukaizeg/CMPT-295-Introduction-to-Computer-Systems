#include "str_cmp.h"

/**
 * @brief Compare two strings
 *
 * @param s1
 * @param s2
 * @return int
 */
int my_str_cmp(const char* s1, const char* s2)
{
    // TODO: Compare two character arrays. return 0 if they match, 1 otherwise
    // You can assume that s1 and s2 are null terminated strings.
    // WARNING: strings could potentially be of different lengths
    // e.g., "apple" does not match "apple " (which includes the extra space).
    // Value to be returned will be 1.
    // You cannot use any of the string helper functions including strlen and
    // strncmp, strcmp.
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
        {
            return 1;
        }
        s1++;
        s2++;
    }
    if (*s1 == 0 && *s2 == 0)
    {
        return 0;
    }
    return 1;
}
