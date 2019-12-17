#include "MD4.h"

void MD4::copy64(uint32 *M, const unsigned char *in)
{
	int i;

	for (i = 0; i < 16; i++)
		M[i] = (in[i * 4 + 3] << 24) | (in[i * 4 + 2] << 16) |
		(in[i * 4 + 1] << 8) | (in[i * 4 + 0] << 0);
}

void MD4::mdfour64(uint32 *M) {
	int j;
	uint32 AA, BB, CC, DD;
	uint32 X[16];

	for (j = 0; j < 16; j++)
		X[j] = M[j];

	AA = A; BB = B; CC = C; DD = D;

	ROUND1(A, B, C, D, 0, 3);  ROUND1(D, A, B, C, 1, 7);
	ROUND1(C, D, A, B, 2, 11);  ROUND1(B, C, D, A, 3, 19);
	ROUND1(A, B, C, D, 4, 3);  ROUND1(D, A, B, C, 5, 7);
	ROUND1(C, D, A, B, 6, 11);  ROUND1(B, C, D, A, 7, 19);
	ROUND1(A, B, C, D, 8, 3);  ROUND1(D, A, B, C, 9, 7);
	ROUND1(C, D, A, B, 10, 11);  ROUND1(B, C, D, A, 11, 19);
	ROUND1(A, B, C, D, 12, 3);  ROUND1(D, A, B, C, 13, 7);
	ROUND1(C, D, A, B, 14, 11);  ROUND1(B, C, D, A, 15, 19);

	ROUND2(A, B, C, D, 0, 3);  ROUND2(D, A, B, C, 4, 5);
	ROUND2(C, D, A, B, 8, 9);  ROUND2(B, C, D, A, 12, 13);
	ROUND2(A, B, C, D, 1, 3);  ROUND2(D, A, B, C, 5, 5);
	ROUND2(C, D, A, B, 9, 9);  ROUND2(B, C, D, A, 13, 13);
	ROUND2(A, B, C, D, 2, 3);  ROUND2(D, A, B, C, 6, 5);
	ROUND2(C, D, A, B, 10, 9);  ROUND2(B, C, D, A, 14, 13);
	ROUND2(A, B, C, D, 3, 3);  ROUND2(D, A, B, C, 7, 5);
	ROUND2(C, D, A, B, 11, 9);  ROUND2(B, C, D, A, 15, 13);

	ROUND3(A, B, C, D, 0, 3);  ROUND3(D, A, B, C, 8, 9);
	ROUND3(C, D, A, B, 4, 11);  ROUND3(B, C, D, A, 12, 15);
	ROUND3(A, B, C, D, 2, 3);  ROUND3(D, A, B, C, 10, 9);
	ROUND3(C, D, A, B, 6, 11);  ROUND3(B, C, D, A, 14, 15);
	ROUND3(A, B, C, D, 1, 3);  ROUND3(D, A, B, C, 9, 9);
	ROUND3(C, D, A, B, 5, 11);  ROUND3(B, C, D, A, 13, 15);
	ROUND3(A, B, C, D, 3, 3);  ROUND3(D, A, B, C, 11, 9);
	ROUND3(C, D, A, B, 7, 11);  ROUND3(B, C, D, A, 15, 15);

	A += AA; B += BB; C += CC; D += DD;

	A &= 0xFFFFFFFF; B &= 0xFFFFFFFF;
	C &= 0xFFFFFFFF; D &= 0xFFFFFFFF;

	for (j = 0; j < 16; j++)
		X[j] = 0;
}


void MD4::mdfour(unsigned char *out, const unsigned char *in, int n){
	unsigned char buf[128];
	uint32 M[16];
	uint32 b = n * 8;
	int i;

	A = 0x67452301;
	B = 0xefcdab89;
	C = 0x98badcfe;
	D = 0x10325476;

	while (n > 64) {
		copy64(M, in);
		mdfour64(M);
		in += 64;
		n -= 64;
	}

	for (i = 0; i < 128; i++)
		buf[i] = 0;
	memcpy(buf, in, n);
	buf[n] = 0x80;

	if (n <= 55) {
		copy4(buf + 56, b);
		copy64(M, buf);
		mdfour64(M);
	}
	else {
		copy4(buf + 120, b);
		copy64(M, buf);
		mdfour64(M);
		copy64(M, buf + 64);
		mdfour64(M);
	}

	for (i = 0; i < 128; i++)
		buf[i] = 0;
	copy64(M, buf);

	copy4(out, A);
	copy4(out + 4, B);
	copy4(out + 8, C);
	copy4(out + 12, D);

	A = B = C = D = 0;
}