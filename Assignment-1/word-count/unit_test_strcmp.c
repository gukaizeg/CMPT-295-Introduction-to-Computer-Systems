// WRITE YOUR OWN
// Build  gcc -I ./include/ unit_test_strcmp.c str_cmp.c -o unit_test_str_cmp.bin

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "str_cmp.h"

int main(int argc, char* argv[])
{
    assert(my_str_cmp("Ava", "") == 1);
    assert(my_str_cmp("", "csd d") == 1);
    assert(my_str_cmp("", "") == 0);
    assert(my_str_cmp("Ab ", "Ab ") == 0);
    assert(my_str_cmp("ABC ", "ABC  ") == 1);
    assert(my_str_cmp("1234", "123") == 1);
    assert(my_str_cmp("123", "12334") == 1);
    assert(my_str_cmp("ABC", "abc") == 1);
    assert(my_str_cmp("12345", "1234a") == 1);
    return 0;
}


