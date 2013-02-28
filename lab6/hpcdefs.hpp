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

#if defined(__GNUC__)
	// gcc or gcc-compatible compiler
	#define CSE6230_RESTRICT __restrict__
#elif defined(_MSC_VER)
	// msvc or msvc-compatible compiler
	#define CSE6230_RESTRICT __restrict
#else
	#warning Compiler is not recognized and restrict qualifier is not used.
	#define CSE6230_RESTRICT
#endif

#if defined(__GNUC__)
	#if defined(__MMX__)
		#define CSE6230_MMX_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE__)
		#define CSE6230_SSE_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE2__)
		#define CSE6230_SSE2_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE3__)
		#define CSE6230_SSE3_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSSE3__)
		#define CSE6230_SSSE3_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE4A__)
		#define CSE6230_SSE4A_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE4_1__)
		#define CSE6230_SSE4_1_INTRINSICS_SUPPORTED
	#endif
	#if defined(__SSE4_2__)
		#define CSE6230_SSE4_2_INTRINSICS_SUPPORTED
	#endif
	#if defined(__AVX__)
		#define CSE6230_AVX_INTRINSICS_SUPPORTED
	#endif
	#if defined(__FMA4__) || defined(__FMA3__)
		#define CSE6230_FMA_INTRINSICS_SUPPORTED
	#endif
	#if defined(__XOP__)
		#define CSE6230_XOP_INTRINSICS_SUPPORTED
	#endif
#elif defined(_MSC_VER)
	#if defined(_M_IX86) || defined(_M_X64)
		#define CSE6230_MMX_INTRINSICS_SUPPORTED
		#define CSE6230_SSE_INTRINSICS_SUPPORTED
		#define CSE6230_SSE2_INTRINSICS_SUPPORTED
		#if _MSC_VER >= 1400 // Visual Studio 2005
			#define CSE6230_SSE3_INTRINSICS_SUPPORTED
		#endif
		#if _MSC_VER >= 1500 // Visual Studio 2008
			#define CSE6230_SSSE3_INTRINSICS_SUPPORTED
			#define CSE6230_SSE4A_INTRINSICS_SUPPORTED
			#define CSE6230_SSE4_1_INTRINSICS_SUPPORTED
			#define CSE6230_SSE4_2_INTRINSICS_SUPPORTED
		#endif
		#if _MSC_VER >= 1600 // Visual Studio 2010
			#define CSE6230_AVX_INTRINSICS_SUPPORTED
		#endif
		#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 160040219) // Visual Studio 2010 SP1
			#define CSE6230_FMA_INTRINSICS_SUPPORTED
			#define CSE6230_XOP_INTRINSICS_SUPPORTED
		#endif
	#endif
#else
	#warning Compiler is not recognized and intrinsic functions are not used.
#endif

#include <stddef.h>
#ifdef _MSC_VER
	#include <intrin.h>
	typedef signed __int64 int64_t;
	typedef signed __int32 int32_t;
	typedef signed __int16 int16_t;
	typedef signed __int8 int8_t;
	
	typedef unsigned __int64 uint64_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int8 uint8_t;
#else
	#include <stdint.h>
#endif

#if defined(__GNUC__)
	#if defined(__x86_64__)
		#include <x86intrin.h>
	#else
		#error Unsupported architecture
	#endif
#elif defined(_MSC_VER)
	#include <intrin.h>
#else
	#error Unsuppprted compiler
#endif
#include <malloc.h>

inline static uint64_t get_cpu_ticks_acquire() {
	#if defined(__GNUC__)
		#ifdef __x86_64__
			uint32_t low, high;
			__asm__ __volatile__ (
				"xor %%eax, %%eax;"
				"cpuid;"
				"rdtsc;"
			: "=a"(low), "=d"(high)
			:
			: "%rbx", "%rcx"
			);
			return (uint64_t(high) << 32) | uint64_t(low);
		#endif
	#elif defined(_MSC_VER)
		int registers[4];
		__cpuid(registers, 0);
		_ReadWriteBarrier();
		return __rdtsc();
	#else
		#error Unsupported compiler
	#endif
}

inline static uint64_t get_cpu_ticks_release() {
	#if defined(__GNUC__)
		#ifdef __x86_64__
			uint32_t low, high;
			#ifdef CSE6230_USE_RDTSCP
				asm volatile (
					"rdtscp;"
				: "=a"(low), "=d"(high)
				:
				: "%rcx"
				);
			#else
				__asm__ __volatile__ (
					"xor %%eax, %%eax;"
					"cpuid;"
					"rdtsc;"
				: "=a"(low), "=d"(high)
				:
				: "%rbx", "%rcx"
				);
			#endif
			return (uint64_t(high) << 32) | uint64_t(low);
		#else
			#error Unsupported architecture
		#endif
	#elif defined(_MSC_VER)
		#ifdef CSE6230_USE_RDTSCP
			return __rdtscp();
		#else
			int registers[4];
			__cpuid(registers, 0);
			_ReadWriteBarrier();
			return __rdtsc();
		#endif
	#else
		#error Unsupported compiler
	#endif
}

inline static void* aligned_alloc(size_t allocation_size, size_t alignment) {
	#ifdef _MSC_VER
		// Microsoft flavor
		return _aligned_malloc(allocation_size, alignment);
	#else
		// Unix flavor
		return memalign(alignment, allocation_size);
	#endif
}

inline static void aligned_free(void* memory_pointer) {
	#ifdef _MSC_VER
		// Microsoft flavor
		_aligned_free(memory_pointer);
	#else
		// Unix flavor
		free(memory_pointer);
	#endif
}
