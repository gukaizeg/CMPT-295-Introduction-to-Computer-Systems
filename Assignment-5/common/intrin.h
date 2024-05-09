// Define vector unit width here
#define VLEN 8

#ifndef cs295INTRIN_H_
#define cs295INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger cs295Logger;

template <typename T>
struct __cs295_vec {
  T value[VLEN];
};

// Declare a mask with __cs295_mask
struct __cs295_mask : __cs295_vec<bool> {};

// Declare a floating point vector register with __cs295_vec_float
#define __cs295_vec_float __cs295_vec<float>

// Declare an integer vector register with __cs295_vec_int
#define __cs295_vec_int   __cs295_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__cs295_mask _cs295_init_ones(int first = VLEN);

// Return the inverse of maska
__cs295_mask _cs295_mask_not(__cs295_mask &maska);

// Return (maska | maskb)
__cs295_mask _cs295_mask_or(__cs295_mask &maska, __cs295_mask &maskb);

// Return (maska & maskb)
__cs295_mask _cs295_mask_and(__cs295_mask &maska, __cs295_mask &maskb);

// Count the number of 1s in maska
int _cs295_cntbits(__cs295_mask &maska);

// Return index of first one in the mask from the left e.g., [0,1,0,1,0,1] return 1. since mask[1] = 1.
int _cs295_firstbit(__cs295_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _cs295_vset_float(__cs295_vec_float &vecResult, float value, __cs295_mask &mask);
void _cs295_vset_int(__cs295_vec_int &vecResult, int value, __cs295_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__cs295_vec_float _cs295_vset_float(float value);
__cs295_vec_int _cs295_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _cs295_vmove_float(__cs295_vec_float &dest, __cs295_vec_float &src, __cs295_mask &mask);
void _cs295_vmove_int(__cs295_vec_int &dest, __cs295_vec_int &src, __cs295_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _cs295_vload_float(__cs295_vec_float &dest, float* src, __cs295_mask &mask);
void _cs295_vload_int(__cs295_vec_int &dest, int* src, __cs295_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _cs295_vstore_float(float* dest, __cs295_vec_float &src, __cs295_mask &mask);
void _cs295_vstore_int(int* dest, __cs295_vec_int &src, __cs295_mask &mask);

// Indexed Loads

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _cs295_vload_index_float(__cs295_vec_float &dest,
                              __cs295_vec_int &index, float *src,
                              __cs295_mask &mask);
void _cs295_vload_index_int(__cs295_vec_int &dest,
                            __cs295_vec_int &index, int *src,
                            __cs295_mask &mask);

// Segmented loads
void _cs295_vload_seg_float(__cs295_vec_float dest[], float *src,
                           __cs295_mask &mask, const int fields);

void _cs295_vload_seg_int(__cs295_vec_int dest[], int *src, __cs295_mask &mask, const int fields);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vadd_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vadd_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vsub_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vsub_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vmult_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vmult_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vdiv_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vdiv_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of (veca >> vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vshiftright_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of (veca & vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vbitand_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _cs295_vabs_float(__cs295_vec_float &vecResult, __cs295_vec_float &veca, __cs295_mask &mask);
void _cs295_vabs_int(__cs295_vec_int &vecResult, __cs295_vec_int &veca, __cs295_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vgt_float(__cs295_mask &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vgt_int(__cs295_mask &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _cs295_vlt_float(__cs295_mask &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_vlt_int(__cs295_mask &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _cs295_veq_float(__cs295_mask &vecResult, __cs295_vec_float &veca, __cs295_vec_float &vecb, __cs295_mask &mask);
void _cs295_veq_int(__cs295_mask &vecResult, __cs295_vec_int &veca, __cs295_vec_int &vecb, __cs295_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _cs295_hadd_float(__cs295_vec_float &vecResult, __cs295_vec_float &vec);
void _cs295_hadd_int(__cs295_vec_int &vecResult, __cs295_vec_int &vec);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _cs295_reduce_add_float(float &result, __cs295_vec_float &vec,
                             __cs295_mask &mask);
void _cs295_reduce_add_int(int &result, __cs295_vec_int &vec,
                           __cs295_mask &mask);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _cs295_interleave_float(__cs295_vec_float &vecResult, __cs295_vec_float &vec);
void _cs295_interleave_int(__cs295_vec_int &vecResult, __cs295_vec_int &vec);
// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif
