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

#include <stdint.h>
#pragma once

namespace xorshift {
	
	class rng {
	public:
		rng() {
			this->state = 88172645463325252LL;
		}
		
		inline uint64_t get_uint64() {
			this->state ^= (this->state << 13);
			this->state ^= (this->state >> 7);
			this->state ^= (this->state << 17);
			return this->state;
		}
		
		inline uint32_t get_uint32() {
			return static_cast<uint32_t>(this->get_uint64());
		}
		
		inline float get_float() {
			int32_t x = this->get_uint32() & 0x00FFFFFF; // 24 bits
			return float(x) / 16777216.0f;
		}
	private:
		uint64_t offset;
		uint64_t period;
		uint64_t threshold;
		uint64_t state;
	};
	
}