#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"

using namespace std;

void imaxSerial(int* values, int* output, int N)
{
    int x = 0xffffffff;
    int index = 0;
    for (int i = 0; i < N; i++)
    {
        if (values[i] > x)
        {
            x = values[i];
            index = i;
        }
    }
    *output = index;
}

// implementation of imax using instrinsics
void imaxVector(int* values, int* output, int N)
{
    int globalMax = 0;
    for (int i = 0; i < N; i += VLEN)
    {
        int width = VLEN;
        if (N - i < VLEN)
        {
            width = N - i;
        }

        __cs295_mask maskAll = _cs295_init_ones(width);

        __cs295_vec_int v_x;
        _cs295_vload_int(v_x, values + i, maskAll);

        int vlenMax = i;

        __cs295_mask mask = _cs295_init_ones(width);
        while (1)
        {
            __cs295_vec_int v_a;
            _cs295_vset_int(v_a, values[vlenMax], maskAll);
            _cs295_vgt_int(mask, v_x, v_a, mask);
           
            if (_cs295_cntbits(mask)==0)
            {
                break;
            }
            int begin = _cs295_firstbit(mask);
            vlenMax = i + begin;
        }

        if (values[globalMax] < values[vlenMax])
        {
            globalMax = vlenMax;
        }
    }

    output[0] = globalMax;

}