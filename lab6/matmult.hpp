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

#pragma once

#include <hpcdefs.hpp>

typedef void (*matrix4x4_mul_function)(const float*, const float*, float*, size_t);

extern "C" void matrix4x4_mul_supernaive(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
extern "C" void matrix4x4_mul_naive(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
#ifdef CSE6230_SSE_INTRINSICS_SUPPORTED
extern "C" void matrix4x4_mul_sse(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
extern "C" void matrix4x4_mul_sse_scalar_load(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
extern "C" void matrix4x4_mul_sse_optimized(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
#endif
#ifdef CSE6230_SSE3_INTRINSICS_SUPPORTED
extern "C" void matrix4x4_mul_sse3(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
#endif
#ifdef CSE6230_SSE4_1_INTRINSICS_SUPPORTED
extern "C" void matrix4x4_mul_sse4_1(const float *CSE6230_RESTRICT aPointer, const float *CSE6230_RESTRICT bPointer, float *CSE6230_RESTRICT cPointer, size_t length);
#endif
