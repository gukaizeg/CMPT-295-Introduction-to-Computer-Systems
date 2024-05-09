// Define vector unit width here
#define VECTOR_WIDTH 8

#ifndef SFU295INTRIN_H_
#define SFU295INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger SFU295Logger;

template <typename T>
struct __sfu295_vec
{
  T value[VECTOR_WIDTH];
};

// Declare a mask with __sfu295_mask
struct __sfu295_mask : __sfu295_vec<bool>
{
};

// Declare a floating point vector register with __sfu295_vec_float
#define __sfu295_vec_float __sfu295_vec<float>

// Declare an integer vector register with __sfu295_vec_int
#define __sfu295_vec_int __sfu295_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__sfu295_mask _sfu295_init_ones(int first = VECTOR_WIDTH);

// Return the inverse of maska
__sfu295_mask _sfu295_mask_not(__sfu295_mask &maska);

// Return (maska | maskb)
__sfu295_mask _sfu295_mask_or(__sfu295_mask &maska, __sfu295_mask &maskb);

// Return (maska & maskb)
__sfu295_mask _sfu295_mask_and(__sfu295_mask &maska, __sfu295_mask &maskb);

// Count the number of 1s in maska
int _sfu295_cntbits(__sfu295_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _sfu295_vset_float(__sfu295_vec_float &vecResult, float value, __sfu295_mask &mask);
void _sfu295_vset_int(__sfu295_vec_int &vecResult, int value, __sfu295_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__sfu295_vec_float _sfu295_vset_float(float value);
__sfu295_vec_int _sfu295_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _sfu295_vmove_float(__sfu295_vec_float &dest, __sfu295_vec_float &src, __sfu295_mask &mask);
void _sfu295_vmove_int(__sfu295_vec_int &dest, __sfu295_vec_int &src, __sfu295_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _sfu295_vload_float(__sfu295_vec_float &dest, float *src, __sfu295_mask &mask);
void _sfu295_vload_int(__sfu295_vec_int &dest, int *src, __sfu295_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _sfu295_vstore_float(float *dest, __sfu295_vec_float &src, __sfu295_mask &mask);
void _sfu295_vstore_int(int *dest, __sfu295_vec_int &src, __sfu295_mask &mask);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vadd_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vadd_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vsub_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vsub_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vmult_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vmult_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vdiv_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vdiv_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of (veca >> vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vshiftright_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of (veca & vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vbitand_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _sfu295_vabs_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &veca, __sfu295_mask &mask);
void _sfu295_vabs_int(__sfu295_vec_int &vecResult, __sfu295_vec_int &veca, __sfu295_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vgt_float(__sfu295_mask &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vgt_int(__sfu295_mask &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_vlt_float(__sfu295_mask &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_vlt_int(__sfu295_mask &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _sfu295_veq_float(__sfu295_mask &vecResult, __sfu295_vec_float &veca, __sfu295_vec_float &vecb, __sfu295_mask &mask);
void _sfu295_veq_int(__sfu295_mask &vecResult, __sfu295_vec_int &veca, __sfu295_vec_int &vecb, __sfu295_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _sfu295_hadd_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _sfu295_interleave_float(__sfu295_vec_float &vecResult, __sfu295_vec_float &vec);

// Add a customized log to help debugging
void addUserLog(const char *logStr);

#endif
