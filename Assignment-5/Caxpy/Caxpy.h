#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"

using namespace std;

void CAXPYSerial(int N, int cond[], int a, int X[], int Y[])
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (cond[i]) Y[i] = a * X[i] + Y[i];
    }
}

// implementation of relu using instrinsics
void CAXPYVector(int N, int cond[], int a, int X[], int Y[])
{
    for (int i = 0; i < N; i += VLEN)
    {
        int width = VLEN;
        if (N - i < VLEN)
        {
            width = N - i;
        }
        __cs295_mask maskAll = _cs295_init_ones(width);

        __cs295_vec_int v_a;
        _cs295_vset_int(v_a, a, maskAll);

        __cs295_vec_int v_x;
        _cs295_vload_int(v_x, X + i, maskAll);  

        __cs295_vec_int v_res;
        _cs295_vmult_int(v_res, v_a, v_x, maskAll);

        __cs295_vec_int v_y;
        _cs295_vload_int(v_y, Y + i, maskAll);

        _cs295_vadd_int(v_res, v_res, v_y, maskAll);

        __cs295_vec_int v_cond;
        _cs295_vload_int(v_cond, cond + i, maskAll);

        __cs295_vec_int v_zero;
        _cs295_vset_int(v_zero, 0, maskAll);

        __cs295_mask setMask;
        _cs295_veq_int(setMask, v_cond, v_zero, maskAll);
        setMask = _cs295_mask_not(setMask);
        setMask = _cs295_mask_and(setMask, maskAll);

        _cs295_vstore_int(Y + i, v_res, setMask);
    }
}