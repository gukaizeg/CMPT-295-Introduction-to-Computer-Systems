#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

int SoASerial(int* values, int N)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += values[i];
    }

    return sum;
}
// Assume N % VLEN == 0
// Assume VLEN is a power of 2
int SoAVector(int* values, int N)
{
    int sum = 0;
    int result[VLEN];
    for (int i = 0; i < N; i += VLEN)
    {
        int width = VLEN;

        __cs295_mask maskAll = _cs295_init_ones(width);

        __cs295_vec_int v_x;
        _cs295_vload_int(v_x, values + i, maskAll);

        while(width > 1)
        {
            _cs295_hadd_int(v_x, v_x);
            _cs295_interleave_int(v_x, v_x);
            width /= 2;
        }
        _cs295_vstore_int(result, v_x, maskAll);
        sum += result[0];
    }

    return sum;
}
