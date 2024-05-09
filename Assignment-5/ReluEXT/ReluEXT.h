#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

void ReluSerial(int* values, int* output, int N)
{
    for (int i = 0; i < N; i++)
    {
        int x = values[i];
        if (x < 0)
        {
            output[i] = 0;
        }
        else
        {
            output[i] = x;
        }
    }
}

// implementation of relu using instrinsics
void ReluVector(int* values, int* output, int N)
{
    for (int i = 0; i < N; i += VLEN)
    {
        int width = VLEN;
        if (N - i < VLEN)
        {
            width = N - i;
        }
        __cs295_mask maskAll = _cs295_init_ones(width);

        __cs295_vec_int v_x;
        _cs295_vload_int(v_x, values + i, maskAll);  // x = values[i];

        __cs295_vec_int v_zero;
        _cs295_vset_int(v_zero, 0, maskAll);

        __cs295_mask v_bool;
        _cs295_vlt_int(v_bool, v_x, v_zero, maskAll);
        v_bool = _cs295_mask_not(v_bool);

        __cs295_vec_int v_res;
        _cs295_vset_int(v_res, 0, maskAll);
        _cs295_vmove_int(v_res, v_x, v_bool);

        _cs295_vstore_int(output + i, v_res, maskAll);
    }
}