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
#include <matmult.hpp>
#include <math.h>
#include <iacaMarks.h>

void matrix4x4_mul_supernaive(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				float c = 0.0f;
				for (int k = 0; k < 4; k++) {
					c += aPointer[i * 4 + k] * bPointer[k * 4 + j];
				}
				cPointer[i * 4 + j] = c;
			}
		}
		
		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}

void matrix4x4_mul_naive(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		const float a00 = aPointer[0];
		const float a01 = aPointer[1];
		const float a02 = aPointer[2];
		const float a03 = aPointer[3];
		const float a10 = aPointer[4];
		const float a11 = aPointer[5];
		const float a12 = aPointer[6];
		const float a13 = aPointer[7];
		const float a20 = aPointer[8];
		const float a21 = aPointer[9];
		const float a22 = aPointer[10];
		const float a23 = aPointer[11];
		const float a30 = aPointer[12];
		const float a31 = aPointer[13];
		const float a32 = aPointer[14];
		const float a33 = aPointer[15];

		const float b00 = bPointer[0];
		const float b01 = bPointer[1];
		const float b02 = bPointer[2];
		const float b03 = bPointer[3];
		const float b10 = bPointer[4];
		const float b11 = bPointer[5];
		const float b12 = bPointer[6];
		const float b13 = bPointer[7];
		const float b20 = bPointer[8];
		const float b21 = bPointer[9];
		const float b22 = bPointer[10];
		const float b23 = bPointer[11];
		const float b30 = bPointer[12];
		const float b31 = bPointer[13];
		const float b32 = bPointer[14];
		const float b33 = bPointer[15];

		const float c00 = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
		const float c01 = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
		const float c02 = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
		const float c03 = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;
		const float c10 = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
		const float c11 = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
		const float c12 = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
		const float c13 = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;
		const float c20 = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
		const float c21 = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
		const float c22 = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
		const float c23 = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;
		const float c30 = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
		const float c31 = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
		const float c32 = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
		const float c33 = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;
		
		cPointer[0] = c00;
		cPointer[1] = c01;
		cPointer[2] = c02;
		cPointer[3] = c03;
		cPointer[4] = c10;
		cPointer[5] = c11;
		cPointer[6] = c12;
		cPointer[7] = c13;
		cPointer[8] = c20;
		cPointer[9] = c21;
		cPointer[10] = c22;
		cPointer[11] = c23;
		cPointer[12] = c30;
		cPointer[13] = c31;
		cPointer[14] = c32;
		cPointer[15] = c33;
		
		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}

#ifdef CSE6230_SSE_INTRINSICS_SUPPORTED
void matrix4x4_mul_sse_scalar_load(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		const __m128 a00 = _mm_load_ss(aPointer);
		const __m128 a01 = _mm_load_ss(aPointer + 1);
		const __m128 a02 = _mm_load_ss(aPointer + 2);
		const __m128 a03 = _mm_load_ss(aPointer + 3);
		const __m128 a10 = _mm_load_ss(aPointer + 4);
		const __m128 a11 = _mm_load_ss(aPointer + 5);
		const __m128 a12 = _mm_load_ss(aPointer + 6);
		const __m128 a13 = _mm_load_ss(aPointer + 7);
		const __m128 a20 = _mm_load_ss(aPointer + 8);
		const __m128 a21 = _mm_load_ss(aPointer + 9);
		const __m128 a22 = _mm_load_ss(aPointer + 10);
		const __m128 a23 = _mm_load_ss(aPointer + 11);
		const __m128 a30 = _mm_load_ss(aPointer + 12);
		const __m128 a31 = _mm_load_ss(aPointer + 13);
		const __m128 a32 = _mm_load_ss(aPointer + 14);
		const __m128 a33 = _mm_load_ss(aPointer + 15);

		const __m128 b0 = _mm_load_ps(bPointer);
		const __m128 b1 = _mm_load_ps(bPointer + 4);
		const __m128 b2 = _mm_load_ps(bPointer + 8);
		const __m128 b3 = _mm_load_ps(bPointer + 12);
		
		const __m128 c0 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a00, a00, 0)),
				_mm_mul_ps(b1, _mm_shuffle_ps(a01, a01, 0))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a02, a02, 0)),
				_mm_mul_ps(b3, _mm_shuffle_ps(a03, a03, 0))
			)
		);

		const __m128 c1 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a10, a10, 0)),
				_mm_mul_ps(b1, _mm_shuffle_ps(a11, a11, 0))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a12, a12, 0)),
				_mm_mul_ps(b3, _mm_shuffle_ps(a13, a13, 0))
			)
		);

		const __m128 c2 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a20, a20, 0)),
				_mm_mul_ps(b1, _mm_shuffle_ps(a21, a21, 0))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a22, a22, 0)),
				_mm_mul_ps(b3, _mm_shuffle_ps(a23, a23, 0))
			)
		);

		const __m128 c3 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a30, a30, 0)),
				_mm_mul_ps(b1, _mm_shuffle_ps(a31, a31, 0))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a32, a32, 0)),
				_mm_mul_ps(b3, _mm_shuffle_ps(a33, a33, 0))
			)
		);
		
		_mm_store_ps(cPointer, c0);
		_mm_store_ps(cPointer + 4, c1);
		_mm_store_ps(cPointer + 8, c2);
		_mm_store_ps(cPointer + 12, c3);

		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}

void matrix4x4_mul_sse(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		const __m128 a0 = _mm_load_ps(aPointer);
		const __m128 a1 = _mm_load_ps(aPointer + 4);
		const __m128 a2 = _mm_load_ps(aPointer + 8);
		const __m128 a3 = _mm_load_ps(aPointer + 12);

		const __m128 b0 = _mm_load_ps(bPointer);
		const __m128 b1 = _mm_load_ps(bPointer + 4);
		const __m128 b2 = _mm_load_ps(bPointer + 8);
		const __m128 b3 = _mm_load_ps(bPointer + 12);
		
		const __m128 c0 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c1 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c2 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c3 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);
		
		_mm_store_ps(cPointer, c0);
		_mm_store_ps(cPointer + 4, c1);
		_mm_store_ps(cPointer + 8, c2);
		_mm_store_ps(cPointer + 12, c3);

		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}

void matrix4x4_mul_sse_optimized(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	/* FUNCTION FOR YOU TO OPTIMIZE */
	for (; length != 0; length -= 1) {
		const __m128 a0 = _mm_load_ps(aPointer);
		const __m128 a1 = _mm_load_ps(aPointer + 4);
		const __m128 a2 = _mm_load_ps(aPointer + 8);
		const __m128 a3 = _mm_load_ps(aPointer + 12);

		const __m128 b0 = _mm_load_ps(bPointer);
		const __m128 b1 = _mm_load_ps(bPointer + 4);
		const __m128 b2 = _mm_load_ps(bPointer + 8);
		const __m128 b3 = _mm_load_ps(bPointer + 12);
		
		const __m128 c0 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a0, a0, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c1 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c2 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a2, a2, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);

		const __m128 c3 = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(b0, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(0, 0, 0, 0))),
				_mm_mul_ps(b1, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(1, 1, 1, 1)))
			),
			_mm_add_ps(
				_mm_mul_ps(b2, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(2, 2, 2, 2))),
				_mm_mul_ps(b3, _mm_shuffle_ps(a3, a3, _MM_SHUFFLE(3, 3, 3, 3)))
			)
		);
		
		_mm_store_ps(cPointer, c0);
		_mm_store_ps(cPointer + 4, c1);
		_mm_store_ps(cPointer + 8, c2);
		_mm_store_ps(cPointer + 12, c3);

		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}
#endif

#ifdef CSE6230_SSE3_INTRINSICS_SUPPORTED
void matrix4x4_mul_sse3(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		const __m128 a0 = _mm_load_ps(aPointer);
		const __m128 a1 = _mm_load_ps(aPointer + 4);
		const __m128 a2 = _mm_load_ps(aPointer + 8);
		const __m128 a3 = _mm_load_ps(aPointer + 12);

		__m128 b0 = _mm_load_ps(bPointer);
		__m128 b1 = _mm_load_ps(bPointer + 4);
		__m128 b2 = _mm_load_ps(bPointer + 8);
		__m128 b3 = _mm_load_ps(bPointer + 12);
		
		_MM_TRANSPOSE4_PS(b0, b1, b2, b3);
		
		const __m128 c0 = _mm_hadd_ps(
			_mm_hadd_ps(_mm_mul_ps(a0, b0), _mm_mul_ps(a0, b1)),
			_mm_hadd_ps(_mm_mul_ps(a0, b2), _mm_mul_ps(a0, b3))
		);
		
		const __m128 c1 = _mm_hadd_ps(
			_mm_hadd_ps(_mm_mul_ps(a1, b0), _mm_mul_ps(a1, b1)),
			_mm_hadd_ps(_mm_mul_ps(a1, b2), _mm_mul_ps(a1, b3))
		);
		
		const __m128 c2 = _mm_hadd_ps(
			_mm_hadd_ps(_mm_mul_ps(a2, b0), _mm_mul_ps(a2, b1)),
			_mm_hadd_ps(_mm_mul_ps(a2, b2), _mm_mul_ps(a2, b3))
		);
		
		const __m128 c3 = _mm_hadd_ps(
			_mm_hadd_ps(_mm_mul_ps(a3, b0), _mm_mul_ps(a3, b1)),
			_mm_hadd_ps(_mm_mul_ps(a3, b2), _mm_mul_ps(a3, b3))
		);
		
		_mm_store_ps(cPointer, c0);
		_mm_store_ps(cPointer + 4, c1);
		_mm_store_ps(cPointer + 8, c2);
		_mm_store_ps(cPointer + 12, c3);

		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}
#endif

#ifdef CSE6230_SSE3_INTRINSICS_SUPPORTED
void matrix4x4_mul_sse4_1(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length) {
	for (; length != 0; length -= 1) {
		const __m128 a0 = _mm_load_ps(aPointer);
		const __m128 a1 = _mm_load_ps(aPointer + 4);
		const __m128 a2 = _mm_load_ps(aPointer + 8);
		const __m128 a3 = _mm_load_ps(aPointer + 12);

		__m128 b0 = _mm_load_ps(bPointer);
		__m128 b1 = _mm_load_ps(bPointer + 4);
		__m128 b2 = _mm_load_ps(bPointer + 8);
		__m128 b3 = _mm_load_ps(bPointer + 12);
		
		_MM_TRANSPOSE4_PS(b0, b1, b2, b3);
		
		const __m128 c0 = _mm_or_ps(
			_mm_or_ps(_mm_dp_ps(a0, b0, 0xF1), _mm_dp_ps(a0, b1, 0xF2)),
			_mm_or_ps(_mm_dp_ps(a0, b2, 0xF4), _mm_dp_ps(a0, b3, 0xF8))
		);
		
		const __m128 c1 = _mm_or_ps(
			_mm_or_ps(_mm_dp_ps(a1, b0, 0xF1), _mm_dp_ps(a1, b1, 0xF2)),
			_mm_or_ps(_mm_dp_ps(a1, b2, 0xF4), _mm_dp_ps(a1, b3, 0xF8))
		);
		
		const __m128 c2 = _mm_or_ps(
			_mm_or_ps(_mm_dp_ps(a2, b0, 0xF1), _mm_dp_ps(a2, b1, 0xF2)),
			_mm_or_ps(_mm_dp_ps(a2, b2, 0xF4), _mm_dp_ps(a2, b3, 0xF8))
		);
		
		const __m128 c3 = _mm_or_ps(
			_mm_or_ps(_mm_dp_ps(a3, b0, 0xF1), _mm_dp_ps(a3, b1, 0xF2)),
			_mm_or_ps(_mm_dp_ps(a3, b2, 0xF4), _mm_dp_ps(a3, b3, 0xF8))
		);
		
		_mm_store_ps(cPointer, c0);
		_mm_store_ps(cPointer + 4, c1);
		_mm_store_ps(cPointer + 8, c2);
		_mm_store_ps(cPointer + 12, c3);

		aPointer += 16;
		bPointer += 16;
		cPointer += 16;
	}
}
#endif
