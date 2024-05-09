#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "intrin.h"
#include "logger.h"
using namespace std;

void absSerial(float *values, float *output, int N)
{
	for (int i = 0; i < N; i++)
	{
		float x = values[i];
		if (x < 0)
		{
			output[i] = -x;
		}
		else
		{
			output[i] = x;
		}
	}
}

// implementation of absolute value using 15418 instrinsics
void absVector(float *values, float *output, int N)
{
	__sfu431_vec_float x;
	__sfu431_vec_float result;
	__sfu431_vec_float zero = _sfu431_vset_float(0.f);
	__sfu431_mask maskAll, maskIsNegative, maskIsNotNegative;

	//  Note: Take a careful look at this loop indexing.  This example
	//  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
	//  Why is that the case?
	for (int i = 0; i < N; i += VECTOR_WIDTH)
	{

		// All ones
		maskAll = _sfu431_init_ones();

		// All zeros
		maskIsNegative = _sfu431_init_ones(0);

		// Load vector of values from contiguous memory addresses
		_sfu431_vload_float(x, values + i, maskAll); // x = values[i];

		// Set mask according to predicate
		_sfu431_vlt_float(maskIsNegative, x, zero, maskAll); // if (x < 0) {

		// Execute instruction using mask ("if" clause)
		_sfu431_vsub_float(result, zero, x, maskIsNegative); //   output[i] = -x;

		// Inverse maskIsNegative to generate "else" mask
		maskIsNotNegative = _sfu431_mask_not(maskIsNegative); // } else {

		// Execute instruction ("else" clause)
		_sfu431_vload_float(result, values + i, maskIsNotNegative); //   output[i] = x; }

		// Write results back to memory
		_sfu431_vstore_float(output + i, result, maskAll);
	}
}

// Accepts an array of values and an array of exponents
// For each element, compute values[i]^exponents[i] and clamp value to
// 4.18.  Store result in outputs.
// Uses iterative squaring, so that total iterations is proportional
// to the log_2 of the exponent
void clampedExpSerial(float *values, int *exponents, float *output, int N)
{
	for (int i = 0; i < N; i++)
	{
		float x = values[i];
		float result = 1.f;
		int y = exponents[i];
		float xpower = x;
		while (y > 0)
		{
			if (y & 0x1)
				result *= xpower;
			xpower = xpower * xpower;
			y >>= 1;
		}
		if (result > 4.18f)
		{
			result = 4.18f;
		}
		output[i] = result;
	}
}

void clampedExpVector(float *values, int *exponents, float *output, int N)
{
	// TODO: Implement your vectorized version of clampedExpSerial here
	//  ...
}

float arraySumSerial(float *values, int N)
{
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += values[i];
	}

	return sum;
}

// Assume N % VECTOR_WIDTH == 0
// Assume VECTOR_WIDTH is a power of 2
float arraySumVector(float *values, int N)
{
	// TODO: Implement your vectorized version here
	// ...
	return 0.f;
}
