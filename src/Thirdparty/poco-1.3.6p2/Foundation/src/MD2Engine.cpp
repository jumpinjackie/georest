//
// MD2Engine.cpp
//
// $Id: //poco/1.3/Foundation/src/MD2Engine.cpp#2 $
//
// Library: Foundation
// Package: Crypt
// Module:  MD2Engine
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//
// MD2 (RFC 1319) algorithm:
// Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
// rights reserved.
//
// License to copy and use this software is granted for
// non-commercial Internet Privacy-Enhanced Mail provided that it is
// identified as the "RSA Data Security, Inc. MD2 Message Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
//
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
//
// These notices must be retained in any copies of any part of this
// documentation and/or software.
//


#include "Poco/MD2Engine.h"
#include <cstring>


namespace Poco {


MD2Engine::MD2Engine()
{
	_digest.reserve(16);
	reset();
}


MD2Engine::~MD2Engine()
{
	reset();
}

	
void MD2Engine::updateImpl(const void* input_, unsigned inputLen)
{
	const unsigned char* input = (const unsigned char*) input_;
	unsigned int i, index, partLen;

	/* Update number of bytes mod 16 */
	index = _context.count;
	_context.count = (index + inputLen) & 0xf;

	partLen = 16 - index;

	/* Transform as many times as possible.	*/
	if (inputLen >= partLen) 
	{
		std::memcpy(&_context.buffer[index], input, partLen);
		transform(_context.state, _context.checksum, _context.buffer);

		for (i = partLen; i + 15 < inputLen; i += 16)
			transform(_context.state, _context.checksum, &input[i]);

		index = 0;
	}
	else i = 0;

	/* Buffer remaining input */
	std::memcpy(&_context.buffer[index], &input[i], inputLen-i);
}


unsigned MD2Engine::digestLength() const
{
	return DIGEST_SIZE;
}


void MD2Engine::reset()
{
	std::memset(&_context, 0, sizeof(_context));
}


const DigestEngine::Digest& MD2Engine::digest()
{
	static const unsigned char* PADDING[] = 
	{
		(unsigned char*) "",
		(unsigned char*) "\001",
		(unsigned char*) "\002\002",
		(unsigned char*) "\003\003\003",
		(unsigned char*) "\004\004\004\004",
		(unsigned char*) "\005\005\005\005\005",
		(unsigned char*) "\006\006\006\006\006\006",
		(unsigned char*) "\007\007\007\007\007\007\007",
		(unsigned char*) "\010\010\010\010\010\010\010\010",
		(unsigned char*) "\011\011\011\011\011\011\011\011\011",
		(unsigned char*) "\012\012\012\012\012\012\012\012\012\012",
		(unsigned char*) "\013\013\013\013\013\013\013\013\013\013\013",
		(unsigned char*) "\014\014\014\014\014\014\014\014\014\014\014\014",
		(unsigned char*) "\015\015\015\015\015\015\015\015\015\015\015\015\015",
		(unsigned char *) "\016\016\016\016\016\016\016\016\016\016\016\016\016\016",
		(unsigned char *) "\017\017\017\017\017\017\017\017\017\017\017\017\017\017\017",
		(unsigned char *) "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
	};
	unsigned int index, padLen;

	/* Pad out to multiple of 16. */
	index = _context.count;
	padLen = 16 - index;
	update((const char*) PADDING[padLen], padLen);

	/* Extend with checksum */
	update((const char*) _context.checksum, 16);

	/* Store state in digest */
	_digest.clear();
	_digest.insert(_digest.begin(), _context.state, _context.state + 16);

	/* Zeroize sensitive information. */
	std::memset(&_context, 0, sizeof(_context));
	reset();
	return _digest;
}


void MD2Engine::transform(unsigned char state[16], unsigned char checksum[16], const unsigned char block[16])
{
	// Permutation of 0..255 constructed from the digits of pi. It gives a
	// "random" nonlinear byte substitution operation.
	static const unsigned char PI_SUBST[256] = 
	{
		41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
		19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
		76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
		138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
		245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
		148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
		39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
		181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
		150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
		112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
		96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
		85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
		234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
		129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
		8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
		203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
		166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
		31, 26, 219, 153, 141, 51, 159, 17, 131, 20
	};
	unsigned int i, j, t;
	unsigned char x[48];

	/* Form encryption block from state, block, state ^ block. */
	std::memcpy(x, state, 16);
	std::memcpy(x+16, block, 16);
	for (i = 0; i < 16; i++)
		x[i+32] = state[i] ^ block[i];

	/* Encrypt block (18 rounds). */
	t = 0;
	for (i = 0; i < 18; i++) 
	{
		for (j = 0; j < 48; j++)
			t = x[j] ^= PI_SUBST[t];
		t = (t + i) & 0xff;
	}

	/* Save new state */
	std::memcpy(state, x, 16);

	/* Update checksum. */
	t = checksum[15];
	for (i = 0; i < 16; i++)
	t = checksum[i] ^= PI_SUBST[block[i] ^ t];

	/* Zeroize sensitive information. */
	std::memset(x, 0, sizeof(x));
}


} // namespace Poco
