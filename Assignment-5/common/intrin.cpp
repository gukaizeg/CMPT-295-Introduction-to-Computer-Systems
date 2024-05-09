#include "intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__cs295_mask _cs295_init_ones(int first) {
  __cs295_mask mask;
  for (int i = 0; i < VLEN; i++) {
    mask.value[i] = (i < first) ? true : false;
  }
  return mask;
}

__cs295_mask _cs295_mask_not(__cs295_mask &maska) {
  __cs295_mask resultMask;
  for (int i = 0; i < VLEN; i++) {
    resultMask.value[i] = !maska.value[i];
  }
  cs295Logger.addLog("masknot", _cs295_init_ones(), VLEN);
  return resultMask;
}

__cs295_mask _cs295_mask_or(__cs295_mask &maska, __cs295_mask &maskb) {
  __cs295_mask resultMask;
  for (int i = 0; i < VLEN; i++) {
    resultMask.value[i] = maska.value[i] | maskb.value[i];
  }
  cs295Logger.addLog("maskor", _cs295_init_ones(), VLEN);
  return resultMask;
}

__cs295_mask _cs295_mask_and(__cs295_mask &maska, __cs295_mask &maskb) {
  __cs295_mask resultMask;
  for (int i = 0; i < VLEN; i++) {
    resultMask.value[i] = maska.value[i] && maskb.value[i];
  }
  cs295Logger.addLog("maskand", _cs295_init_ones(), VLEN);
  return resultMask;
}

int _cs295_cntbits(__cs295_mask &maska) {
  int count = 0;
  for (int i = 0; i < VLEN; i++) {
    if (maska.value[i])
      count++;
  }
  cs295Logger.addLog("cntbits", _cs295_init_ones(), VLEN);
  return count;
}

int _cs295_firstbit(__cs295_mask &maska) {
  for (int i = 0; i < VLEN; i++) {
    if (maska.value[i]) return i;
  }
  cs295Logger.addLog("firstbits", _cs295_init_ones(), VLEN);
  return 0;
}

template <typename T>
void _cs295_vset(__cs295_vec<T> &vecResult, T value, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
  }
  cs295Logger.addLog("vset", mask, VLEN);
}

template void _cs295_vset<float>(__cs295_vec_float &vecResult, float value,
                                  __cs295_mask &mask);
template void _cs295_vset<int>(__cs295_vec_int &vecResult, int value,
                                __cs295_mask &mask);

void _cs295_vset_float(__cs295_vec_float &vecResult, float value,
                        __cs295_mask &mask) {
  _cs295_vset<float>(vecResult, value, mask);
}
void _cs295_vset_int(__cs295_vec_int &vecResult, int value,
                      __cs295_mask &mask) {
  _cs295_vset<int>(vecResult, value, mask);
}

__cs295_vec_float _cs295_vset_float(float value) {
  __cs295_vec_float vecResult;
  __cs295_mask mask = _cs295_init_ones();
  _cs295_vset_float(vecResult, value, mask);
  return vecResult;
}
__cs295_vec_int _cs295_vset_int(int value) {
  __cs295_vec_int vecResult;
  __cs295_mask mask = _cs295_init_ones();
  _cs295_vset_int(vecResult, value, mask);
  return vecResult;
}

template <typename T>
void _cs295_vmove(__cs295_vec<T> &dest, __cs295_vec<T> &src,
                   __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
  }
  cs295Logger.addLog("vmove", mask, VLEN);
}

template void _cs295_vmove<float>(__cs295_vec_float &dest,
                                   __cs295_vec_float &src,
                                   __cs295_mask &mask);
template void _cs295_vmove<int>(__cs295_vec_int &dest, __cs295_vec_int &src,
                                 __cs295_mask &mask);

void _cs295_vmove_float(__cs295_vec_float &dest, __cs295_vec_float &src,
                         __cs295_mask &mask) {
  _cs295_vmove<float>(dest, src, mask);
}
void _cs295_vmove_int(__cs295_vec_int &dest, __cs295_vec_int &src,
                       __cs295_mask &mask) {
  _cs295_vmove<int>(dest, src, mask);
}

template <typename T>
void _cs295_vload(__cs295_vec<T> &dest, T *src, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
  }
  cs295Logger.addLog("vload", mask, VLEN);
}

template void _cs295_vload<float>(__cs295_vec_float &dest, float *src,
                                   __cs295_mask &mask);
template void _cs295_vload<int>(__cs295_vec_int &dest, int *src,
                                 __cs295_mask &mask);

void _cs295_vload_float(__cs295_vec_float &dest, float *src,
                         __cs295_mask &mask) {
  _cs295_vload<float>(dest, src, mask);
}
void _cs295_vload_int(__cs295_vec_int &dest, int *src, __cs295_mask &mask) {
  _cs295_vload<int>(dest, src, mask);
}

template <typename T>
void _cs295_vload_index(__cs295_vec<T> &dest, __cs295_vec_int &index, T *src,
                        __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    dest.value[i] = mask.value[i] ? src[index.value[i]] : dest.value[i];
  }
  cs295Logger.addLog("vload_index", mask, VLEN);
}

template void _cs295_vload_index<float>(__cs295_vec_float &dest,
                                        __cs295_vec_int &index, float *src,
                                        __cs295_mask &mask);
template void _cs295_vload_index<int>(__cs295_vec_int &dest,
                                      __cs295_vec_int &index, int *src,
                                      __cs295_mask &mask);

void _cs295_vload_index_float(__cs295_vec_float &dest, __cs295_vec_int &index,
                               float *src, __cs295_mask &mask) {
  _cs295_vload_index<float>(dest, index, src, mask);
}
void _cs295_vload_index_int(__cs295_vec_int &dest, __cs295_vec_int &index,
                            int *src, __cs295_mask &mask) {
  _cs295_vload_index<int>(dest, index, src, mask);
}

template <typename T>
void _cs295_vload_seg(__cs295_vec<T> dest[], T *src, __cs295_mask &mask,
                       const int fields) {
  for (int i = 0; i < fields; i++) {
    for (int j = 0; j < VLEN; j++) {
      dest[i].value[j] =
          mask.value[j] ? src[(i * fields) + j] : dest[i].value[j];
    }
    cs295Logger.addLog("vlseg", mask, VLEN);
  }
}

void _cs295_vload_seg_float(__cs295_vec_float dest[], float *src,
                             __cs295_mask &mask, const int fields) {
  _cs295_vload_seg<float>(dest, src, mask, fields);
}

void _cs295_vload_seg_int(__cs295_vec_int dest[], int *src,
                           __cs295_mask &mask, const int fields) {
  _cs295_vload_seg<int>(dest, src, mask, fields);
}

template <typename T>
void _cs295_vstore(T *dest, __cs295_vec<T> &src, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    dest[i] = mask.value[i] ? src.value[i] : dest[i];
  }
  cs295Logger.addLog("vstore", mask, VLEN);
}

template void _cs295_vstore<float>(float *dest, __cs295_vec_float &src,
                                    __cs295_mask &mask);
template void _cs295_vstore<int>(int *dest, __cs295_vec_int &src,
                                  __cs295_mask &mask);

void _cs295_vstore_float(float *dest, __cs295_vec_float &src,
                          __cs295_mask &mask) {
  _cs295_vstore<float>(dest, src, mask);
}
void _cs295_vstore_int(int *dest, __cs295_vec_int &src, __cs295_mask &mask) {
  _cs295_vstore<int>(dest, src, mask);
}

template <typename T>
void _cs295_vadd(__cs295_vec<T> &vecResult, __cs295_vec<T> &veca,
                  __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
  }
  cs295Logger.addLog("vadd", mask, VLEN);
}

template void _cs295_vadd<float>(__cs295_vec_float &vecResult,
                                  __cs295_vec_float &veca,
                                  __cs295_vec_float &vecb,
                                  __cs295_mask &mask);
template void _cs295_vadd<int>(__cs295_vec_int &vecResult,
                                __cs295_vec_int &veca, __cs295_vec_int &vecb,
                                __cs295_mask &mask);

void _cs295_vadd_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca,
                        __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_vadd<float>(vecResult, veca, vecb, mask);
}
void _cs295_vadd_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                      __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vadd<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _cs295_vsub(__cs295_vec<T> &vecResult, __cs295_vec<T> &veca,
                  __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
  }
  cs295Logger.addLog("vsub", mask, VLEN);
}

template void _cs295_vsub<float>(__cs295_vec_float &vecResult,
                                  __cs295_vec_float &veca,
                                  __cs295_vec_float &vecb,
                                  __cs295_mask &mask);
template void _cs295_vsub<int>(__cs295_vec_int &vecResult,
                                __cs295_vec_int &veca, __cs295_vec_int &vecb,
                                __cs295_mask &mask);

void _cs295_vsub_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca,
                        __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_vsub<float>(vecResult, veca, vecb, mask);
}
void _cs295_vsub_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                      __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vsub<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _cs295_vmult(__cs295_vec<T> &vecResult, __cs295_vec<T> &veca,
                   __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
  }
  cs295Logger.addLog("vmult", mask, VLEN);
}

template void _cs295_vmult<float>(__cs295_vec_float &vecResult,
                                   __cs295_vec_float &veca,
                                   __cs295_vec_float &vecb,
                                   __cs295_mask &mask);
template void _cs295_vmult<int>(__cs295_vec_int &vecResult,
                                 __cs295_vec_int &veca, __cs295_vec_int &vecb,
                                 __cs295_mask &mask);

void _cs295_vmult_float(__cs295_vec_float &vecResult,
                         __cs295_vec_float &veca, __cs295_vec_float &vecb,
                         __cs295_mask &mask) {
  _cs295_vmult<float>(vecResult, veca, vecb, mask);
}
void _cs295_vmult_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                       __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vmult<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _cs295_vdiv(__cs295_vec<T> &vecResult, __cs295_vec<T> &veca,
                  __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
  }
  cs295Logger.addLog("vdiv", mask, VLEN);
}

void _cs295_vshiftright_int(__cs295_vec_int &vecResult,
                             __cs295_vec_int &veca, __cs295_vec_int &vecb,
                             __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++)
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] >> vecb.value[i]) : vecResult.value[i];
}

void _cs295_vbitand_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                         __cs295_vec_int &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++)
    vecResult.value[i] =
        mask.value[i] ? (veca.value[i] & vecb.value[i]) : vecResult.value[i];
}

template void _cs295_vdiv<float>(__cs295_vec_float &vecResult,
                                  __cs295_vec_float &veca,
                                  __cs295_vec_float &vecb,
                                  __cs295_mask &mask);
template void _cs295_vdiv<int>(__cs295_vec_int &vecResult,
                                __cs295_vec_int &veca, __cs295_vec_int &vecb,
                                __cs295_mask &mask);

void _cs295_vdiv_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca,
                        __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_vdiv<float>(vecResult, veca, vecb, mask);
}
void _cs295_vdiv_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                      __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vdiv<int>(vecResult, veca, vecb, mask);
}

template <typename T>
void _cs295_vabs(__cs295_vec<T> &vecResult, __cs295_vec<T> &veca,
                  __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    vecResult.value[i] =
        mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
  }
  cs295Logger.addLog("vabs", mask, VLEN);
}

template void _cs295_vabs<float>(__cs295_vec_float &vecResult,
                                  __cs295_vec_float &veca,
                                  __cs295_mask &mask);
template void _cs295_vabs<int>(__cs295_vec_int &vecResult,
                                __cs295_vec_int &veca, __cs295_mask &mask);

void _cs295_vabs_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca,
                        __cs295_mask &mask) {
  _cs295_vabs<float>(vecResult, veca, mask);
}
void _cs295_vabs_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca,
                      __cs295_mask &mask) {
  _cs295_vabs<int>(vecResult, veca, mask);
}

template <typename T>
void _cs295_vgt(__cs295_mask &maskResult, __cs295_vec<T> &veca,
                 __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
  }
  cs295Logger.addLog("vgt", mask, VLEN);
}

template void _cs295_vgt<float>(__cs295_mask &maskResult,
                                 __cs295_vec_float &veca,
                                 __cs295_vec_float &vecb, __cs295_mask &mask);
template void _cs295_vgt<int>(__cs295_mask &maskResult,
                               __cs295_vec_int &veca, __cs295_vec_int &vecb,
                               __cs295_mask &mask);

void _cs295_vgt_float(__cs295_mask &maskResult, __cs295_vec_float &veca,
                       __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_vgt<float>(maskResult, veca, vecb, mask);
}
void _cs295_vgt_int(__cs295_mask &maskResult, __cs295_vec_int &veca,
                     __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vgt<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _cs295_vlt(__cs295_mask &maskResult, __cs295_vec<T> &veca,
                 __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
  }
  cs295Logger.addLog("vlt", mask, VLEN);
}

template void _cs295_vlt<float>(__cs295_mask &maskResult,
                                 __cs295_vec_float &veca,
                                 __cs295_vec_float &vecb, __cs295_mask &mask);
template void _cs295_vlt<int>(__cs295_mask &maskResult,
                               __cs295_vec_int &veca, __cs295_vec_int &vecb,
                               __cs295_mask &mask);

void _cs295_vlt_float(__cs295_mask &maskResult, __cs295_vec_float &veca,
                       __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_vlt<float>(maskResult, veca, vecb, mask);
}
void _cs295_vlt_int(__cs295_mask &maskResult, __cs295_vec_int &veca,
                     __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_vlt<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _cs295_veq(__cs295_mask &maskResult, __cs295_vec<T> &veca,
                 __cs295_vec<T> &vecb, __cs295_mask &mask) {
  for (int i = 0; i < VLEN; i++) {
    maskResult.value[i] =
        mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
  }
  cs295Logger.addLog("veq", mask, VLEN);
}

template void _cs295_veq<float>(__cs295_mask &maskResult,
                                 __cs295_vec_float &veca,
                                 __cs295_vec_float &vecb, __cs295_mask &mask);
template void _cs295_veq<int>(__cs295_mask &maskResult,
                               __cs295_vec_int &veca, __cs295_vec_int &vecb,
                               __cs295_mask &mask);

void _cs295_veq_float(__cs295_mask &maskResult, __cs295_vec_float &veca,
                       __cs295_vec_float &vecb, __cs295_mask &mask) {
  _cs295_veq<float>(maskResult, veca, vecb, mask);
}
void _cs295_veq_int(__cs295_mask &maskResult, __cs295_vec_int &veca,
                     __cs295_vec_int &vecb, __cs295_mask &mask) {
  _cs295_veq<int>(maskResult, veca, vecb, mask);
}

template <typename T>
void _cs295_hadd(__cs295_vec<T> &vecResult, __cs295_vec<T> &vec) {
  for (int i = 0; i < VLEN / 2; i++) {
    T result = vec.value[2 * i] + vec.value[2 * i + 1];
    vecResult.value[2 * i] = result;
    vecResult.value[2 * i + 1] = result;
  }
}

template void _cs295_hadd<float>(__cs295_vec_float &vecResult,
                                  __cs295_vec_float &vec);

void _cs295_hadd_float(__cs295_vec_float &vecResult,
                        __cs295_vec_float &vec) {
  _cs295_hadd<float>(vecResult, vec);
}

template void _cs295_hadd<int>(__cs295_vec_int &vecResult,
                                  __cs295_vec_int &vec);

void _cs295_hadd_int(__cs295_vec_int &vecResult,
                        __cs295_vec_int &vec)
{
  _cs295_hadd<int>(vecResult, vec);
}

template <typename T>
void _cs295_reduce_add(T &Result, __cs295_vec<T> &vec, __cs295_mask &mask) {
  Result = 0;
  for (int i = 0; i < VLEN; i++) {
    if (mask.value[i]) {
      Result += vec.value[i];
    }
  }
}

template void _cs295_reduce_add<float>(float &Result, __cs295_vec_float &vec,
                                       __cs295_mask &mask);

void _cs295_reduce_add_float(float &Result, __cs295_vec_float &vec,
                             __cs295_mask &mask) {
  _cs295_reduce_add<float>(Result, vec, mask);
}

template void _cs295_reduce_add<int>(int &Result, __cs295_vec_int &vec,
                                     __cs295_mask &mask);

void _cs295_reduce_add_int(int &Result, __cs295_vec_int &vec,
                           __cs295_mask &mask) {
  _cs295_reduce_add<int>(Result, vec, mask);
}

template <typename T>
void _cs295_interleave(__cs295_vec<T> &vecResult, __cs295_vec<T> &vec) {
  for (int i = 0; i < VLEN; i++) {
    int index =
        i < VLEN / 2 ? (2 * i) : (2 * (i - VLEN / 2) + 1);
    vecResult.value[i] = vec.value[index];
  }
}

template void _cs295_interleave<float>(__cs295_vec_float &vecResult,
                                        __cs295_vec_float &vec);

template void _cs295_interleave<int>(__cs295_vec_int &vecResult,
                                        __cs295_vec_int &vec);

void _cs295_interleave_float(__cs295_vec_float &vecResult,
                              __cs295_vec_float &vec) {
  _cs295_interleave<float>(vecResult, vec);
}

void _cs295_interleave_int(__cs295_vec_int &vecResult,
                              __cs295_vec_int &vec)
{
  _cs295_interleave<int>(vecResult, vec);
}

void addUserLog(const char *logStr) {
  cs295Logger.addLog(logStr, _cs295_init_ones(), 0);
}
