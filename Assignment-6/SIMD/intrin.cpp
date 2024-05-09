#include "intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__sfu295_mask _sfu295_init_ones(int first)
{
    __sfu295_mask mask;
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        mask.value[i] = (i < first) ? true : false;
    }
    return mask;
}

__sfu295_mask _sfu295_mask_not(__sfu295_mask &maska)
{
    __sfu295_mask resultMask;
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        resultMask.value[i] = !maska.value[i];
    }
    SFU295Logger.addLog("masknot", _sfu295_init_ones(), VECTOR_WIDTH);
    return resultMask;
}

__sfu295_mask _sfu295_mask_or(__sfu295_mask &maska, __sfu295_mask &maskb)
{
    __sfu295_mask resultMask;
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        resultMask.value[i] = maska.value[i] | maskb.value[i];
    }
    SFU295Logger.addLog("maskor", _sfu295_init_ones(), VECTOR_WIDTH);
    return resultMask;
}

__sfu295_mask _sfu295_mask_and(__sfu295_mask &maska, __sfu295_mask &maskb)
{
    __sfu295_mask resultMask;
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        resultMask.value[i] = maska.value[i] && maskb.value[i];
    }
    SFU295Logger.addLog("maskand", _sfu295_init_ones(), VECTOR_WIDTH);
    return resultMask;
}

int _sfu295_cntbits(__sfu295_mask &maska)
{
    int count = 0;
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        if (maska.value[i])
            count++;
    }
    SFU295Logger.addLog("cntbits", _sfu295_init_ones(), VECTOR_WIDTH);
    return count;
}

template <typename T>
void _sfu295_vset(__sfu295_vec<T> &vecResult, T value, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
    }
    SFU295Logger.addLog("vset", mask, VECTOR_WIDTH);
}

template void _sfu295_vset<float>(__sfu295_vec_float &vecResult, float value, __sfu295_mask &mask);
template void _sfu295_vset<int>(__sfu295_vec_int &vecResult, int value, __sfu295_mask &mask);

void _sfu295_vset_float(__sfu295_vec_float &vecResult, float value, __sfu295_mask &mask) { _sfu295_vset<float>(vecResult, value, mask); }
void _sfu295_vset_int(__sfu295_vec_int &vecResult, int value, __sfu295_mask &mask) { _sfu295_vset<int>(vecResult, value, mask); }

__sfu295_vec_float _sfu295_vset_float(float value)
{
    __sfu295_vec_float vecResult;
    __sfu295_mask mask = _sfu295_init_ones();
    _sfu295_vset_float(vecResult, value, mask);
    return vecResult;
}
__sfu295_vec_int _sfu295_vset_int(int value)
{
    __sfu295_vec_int vecResult;
    __sfu295_mask mask = _sfu295_init_ones();
    _sfu295_vset_int(vecResult, value, mask);
    return vecResult;
}

template <typename T>
void _sfu295_vmove(__sfu295_vec<T> &dest, __sfu295_vec<T> &src, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
    }
    SFU295Logger.addLog("vmove", mask, VECTOR_WIDTH);
}

template void _sfu295_vmove<float>(__sfu295_vec_float &dest, __sfu295_vec_float &src, __sfu295_mask &mask);
template void _sfu295_vmove<int>(__sfu295_vec_int &dest, __sfu295_vec_int &src, __sfu295_mask &mask);

void _sfu295_vmove_float(__sfu295_vec_float &dest, __sfu295_vec_float &src, __sfu295_mask &mask) { _sfu295_vmove<float>(dest, src, mask); }
void _sfu295_vmove_int(__sfu295_vec_int &dest, __sfu295_vec_int &src, __sfu295_mask &mask) { _sfu295_vmove<int>(dest, src, mask); }

template <typename T>
void _sfu295_vload(__sfu295_vec<T> &dest, T *src, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
    }
    SFU295Logger.addLog("vload", mask, VECTOR_WIDTH);
}

template void _sfu295_vload<float>(__sfu295_vec_float &dest, float *src, __sfu295_mask &mask);
template void _sfu295_vload<int>(__sfu295_vec_int &dest, int *src, __sfu295_mask &mask);

void _sfu295_vload_float(__sfu295_vec_float &dest, float *src, __sfu295_mask &mask) { _sfu295_vload<float>(dest, src, mask); }
void _sfu295_vload_int(__sfu295_vec_int &dest, int *src, __sfu295_mask &mask) { _sfu295_vload<int>(dest, src, mask); }

template <typename T>
void _sfu295_vstore(T *dest, __sfu295_vec<T> &src, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        dest[i] = mask.value[i] ? src.value[i] : dest[i];
    }
    SFU295Logger.addLog("vstore", mask, VECTOR_WIDTH);
}

template void _sfu295_vstore<float>(float *dest, __sfu295_vec_float &src, __sfu295_mask &mask);
template void _sfu295_vstore<int>(int *dest, __sfu295_vec_int &src, __sfu295_mask &mask);

void _sfu295_vstore_float(float *dest, __sfu295_vec_float &src, __sfu295_mask &mask) { _sfu295_vstore<float>(dest, src, mask); }
void _sfu295_vstore_int(int *dest, __sfu295_vec_int &src, __sfu295_mask &mask) { _sfu295_vstore<int>(dest, src, mask); }

template <typename T>
void _sfu295_vadd(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
    }
    SFU295Logger.addLog("vadd", mask, VECTOR_WIDTH);
}

template void _sfu295_vadd<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vadd<int>(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vadd_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vadd<float>(vecResult, veca, vecb, mask); }
void _sfu295_vadd_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vadd<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _sfu295_vsub(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
    }
    SFU295Logger.addLog("vsub", mask, VECTOR_WIDTH);
}

template void _sfu295_vsub<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vsub<int>(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vsub_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vsub<float>(vecResult, veca, vecb, mask); }
void _sfu295_vsub_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vsub<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _sfu295_vmult(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
    }
    SFU295Logger.addLog("vmult", mask, VECTOR_WIDTH);
}

template void _sfu295_vmult<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vmult<int>(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vmult_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vmult<float>(vecResult, veca, vecb, mask); }
void _sfu295_vmult_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vmult<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _sfu295_vdiv(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
    }
    SFU295Logger.addLog("vdiv", mask, VECTOR_WIDTH);
}

void _sfu295_vshiftright_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
        vecResult.value[i] = mask.value[i] ? (veca.value[i] >> vecb.value[i]) : vecResult.value[i];
}

void _sfu295_vbitand_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
        vecResult.value[i] = mask.value[i] ? (veca.value[i] & vecb.value[i]) : vecResult.value[i];
}

template void _sfu295_vdiv<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vdiv<int>(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vdiv_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vdiv<float>(vecResult, veca, vecb, mask); }
void _sfu295_vdiv_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vdiv<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _sfu295_vabs(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &veca, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        vecResult.value[i] = mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
    }
    SFU295Logger.addLog("vabs", mask, VECTOR_WIDTH);
}

template void _sfu295_vabs<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_mask &mask);
template void _sfu295_vabs<int>(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_mask &mask);

void _sfu295_vabs_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_mask &mask) { _sfu295_vabs<float>(vecResult, veca, mask); }
void _sfu295_vabs_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_mask &mask) { _sfu295_vabs<int>(vecResult, veca, mask); }

template <typename T>
void _sfu295_vgt(__sfu295_mask &maskResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        maskResult.value[i] = mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
    }
    SFU295Logger.addLog("vgt", mask, VECTOR_WIDTH);
}

template void _sfu295_vgt<float>(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vgt<int>(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vgt_float(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vgt<float>(maskResult, veca, vecb, mask); }
void _sfu295_vgt_int(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vgt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _sfu295_vlt(__sfu295_mask &maskResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        maskResult.value[i] = mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
    }
    SFU295Logger.addLog("vlt", mask, VECTOR_WIDTH);
}

template void _sfu295_vlt<float>(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_vlt<int>(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_vlt_float(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_vlt<float>(maskResult, veca, vecb, mask); }
void _sfu295_vlt_int(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_vlt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _sfu295_veq(__sfu295_mask &maskResult, __sfu295_vec<T> &veca, __sfu295_vec<T> &vecb, __sfu295_mask &mask)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        maskResult.value[i] = mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
    }
    SFU295Logger.addLog("veq", mask, VECTOR_WIDTH);
}

template void _sfu295_veq<float>(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
template void _sfu295_veq<int>(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

void _sfu295_veq_float(__sfu295_mask &maskResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask) { _sfu295_veq<float>(maskResult, veca, vecb, mask); }
void _sfu295_veq_int(__sfu295_mask &maskResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask) { _sfu295_veq<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _sfu295_hadd(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &vec)
{
    for (int i = 0; i < VECTOR_WIDTH / 2; i++)
    {
        T result = vec.value[2 * i] + vec.value[2 * i + 1];
        vecResult.value[2 * i] = result;
        vecResult.value[2 * i + 1] = result;
    }
}

template void _sfu295_hadd<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec);

void _sfu295_hadd_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec) { _sfu295_hadd<float>(vecResult, vec); }

template <typename T>
void _sfu295_interleave(__sfu295_vec<T> &vecResult, __sfu295_vec<T> &vec)
{
    for (int i = 0; i < VECTOR_WIDTH; i++)
    {
        int index = i < VECTOR_WIDTH / 2 ? (2 * i) : (2 * (i - VECTOR_WIDTH / 2) + 1);
        vecResult.value[i] = vec.value[index];
    }
}

template void _sfu295_interleave<float>(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec);

void _sfu295_interleave_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec) { _sfu295_interleave<float>(vecResult, vec); }

void addUserLog(const char *logStr)
{
    SFU295Logger.addLog(logStr, _sfu295_init_ones(), 0);
}
