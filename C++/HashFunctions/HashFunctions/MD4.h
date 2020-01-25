#pragma once

#include <cstring>

#define ROUND1(a,b,c,d,k,s) a = lshift(a + F(b,c,d) + X[k], s)
#define ROUND2(a,b,c,d,k,s) a = lshift(a + G(b,c,d) + X[k] + (uint32)0x5A827999,s)
#define ROUND3(a,b,c,d,k,s) a = lshift(a + H(b,c,d) + X[k] + (uint32)0x6ED9EBA1,s)

typedef unsigned int uint32;
typedef unsigned char uint8;

class MD4 {
public:
	void mdfour(unsigned char *out, const unsigned char *in, int n);
private:
	void copy64(uint32 *M, const unsigned char *in);
	uint32 A, B, C, D;

	uint32 F(uint32 X, uint32 Y, uint32 Z)
	{
		return (X&Y) | ((~X)&Z);
	}

	uint32 G(uint32 X, uint32 Y, uint32 Z)
	{
		return (X&Y) | (X&Z) | (Y&Z);
	}

	uint32 H(uint32 X, uint32 Y, uint32 Z)
	{
		return X^Y^Z;
	}

	uint32 lshift(uint32 x, int s)
	{
		x &= 0xFFFFFFFF;
		return ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
	}

	void copy4(unsigned char *out, uint32 x)
	{
		out[0] = x & 0xFF;
		out[1] = (x >> 8) & 0xFF;
		out[2] = (x >> 16) & 0xFF;
		out[3] = (x >> 24) & 0xFF;
	}

	void mdfour64(uint32 *M);
};