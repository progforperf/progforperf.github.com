/******************************************************************************\
 *                                                                            *
 * Copyright (c) 2012 Marat Dukhan                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 * claim that you wrote the original software. If you use this software       *
 * in a product, an acknowledgment in the product documentation would be      *
 * appreciated but is not required.                                           *
 *                                                                            *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 * misrepresented as being the original software.                             *
 *                                                                            *
 * 3. This notice may not be removed or altered from any source               *
 * distribution.                                                              *
 *                                                                            *
\******************************************************************************/

#include <hpcdefs.hpp>
#include <xorshift.hpp>
#include <matmult.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif

inline uint64_t min(uint64_t a, uint64_t b) {
	return a < b ? a : b;
}

inline uint64_t max(uint64_t a, uint64_t b) {
	return a > b ? a : b;
}

double compute_max_matrix4x4_error(const float* matrix_array, const float* matrix_array_ref, size_t length) {
	float max_error = 0.0f;
	for (size_t i = 0; i < length * 16; i++) {
		const float error = fabsf(matrix_array[i] - matrix_array_ref[i]);
		if (error > max_error)
			max_error = error;
	}
	return max_error;
}
static void report_timings(const char* method_name, uint64_t ticks, size_t array_size) {
	printf("%31s\t%2.2lf\n", method_name,
		double(ticks) / double(array_size));
}

static void test_matrix4x4_mul(const char* method_name, matrix4x4_mul_function matrix4x4_mul,
	const float* a_array, const float* b_array, float* c_array, float* c_array_ref,
	size_t array_size, size_t experiments_count)
{
	memset(c_array, 0, array_size * sizeof(float) * 16);
	
	matrix4x4_mul(a_array, b_array, c_array, array_size);

	const double absolute_error = compute_max_matrix4x4_error(c_array, c_array_ref, array_size);
	if (!(absolute_error < 1.0e-6f)) {
		fprintf(stderr, "Absolute error is too large (%g) in %s implementation\n", absolute_error, method_name);
		exit(-1);
	}
	
	uint64_t best_ticks = uint64_t(-1);
	for (size_t experiment_number = 1; experiment_number <= experiments_count; experiment_number++) {
		const uint64_t start_ticks = get_cpu_ticks_acquire();
		matrix4x4_mul(a_array, b_array, c_array, array_size);
		const uint64_t end_ticks = get_cpu_ticks_release();
		best_ticks = min(best_ticks, end_ticks - start_ticks);
	}
	report_timings(method_name, best_ticks, array_size);
}
	

static void fill_array(float* array_pointer, size_t length, xorshift::rng& generator) {
	for (size_t index = 0; index < length; index++) {
		array_pointer[index] = generator.get_float();
	}
}

int main(int argc, char** argv) {
#if defined(DEBUG) || defined(_DEBUG)
	const size_t experiments_count = 1000;
#else
	const size_t experiments_count = 100000;
#endif
	
	size_t array_size = 200; // Should fit into L1 cache
	float *a_array = (float*)aligned_alloc(array_size * sizeof(float) * 16, 32);
	float *b_array = (float*)aligned_alloc(array_size * sizeof(float) * 16, 32);
	float *c_array = (float*)aligned_alloc(array_size * sizeof(float) * 16, 32);
	float *c_array_ref = (float*)aligned_alloc(array_size * sizeof(float) * 16, 32);
	xorshift::rng generator = xorshift::rng();
	fill_array(a_array, array_size * 16, generator);
	fill_array(b_array, array_size * 16, generator);
	
	matrix4x4_mul_supernaive(a_array, b_array, c_array_ref, array_size);
	
	printf("%31s\tCPE\n","Stdev Method");

	test_matrix4x4_mul("SuperNaive", &matrix4x4_mul_supernaive, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
	test_matrix4x4_mul("Naive", &matrix4x4_mul_naive, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);

	#ifdef CSE6230_SSE_INTRINSICS_SUPPORTED
		test_matrix4x4_mul("SSE", &matrix4x4_mul_sse, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
		test_matrix4x4_mul("SSE/scalar load", &matrix4x4_mul_sse_scalar_load, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
		test_matrix4x4_mul("SSE + your optimizations", &matrix4x4_mul_sse_optimized, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
	#endif
	#ifdef CSE6230_SSE3_INTRINSICS_SUPPORTED
		test_matrix4x4_mul("SSE3", &matrix4x4_mul_sse3, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
	#endif
	#ifdef CSE6230_SSE4_1_INTRINSICS_SUPPORTED
		test_matrix4x4_mul("SSE4.1", &matrix4x4_mul_sse4_1, a_array, b_array, c_array, c_array_ref, array_size, experiments_count);
	#endif

	aligned_free(a_array);
	aligned_free(b_array);
	aligned_free(c_array);
	aligned_free(c_array_ref);
	
	exit(0);
}