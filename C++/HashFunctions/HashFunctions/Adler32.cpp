#include "Adler32.h"
#include <stddef.h>
#include <stdint.h>

uint32_t ADLER32::adler32(uint32_t crc, unsigned char *buf, size_t len)
{
	uint32_t a = 1, b = 0;

	while (len) {
		unsigned tlen = len > 5550 ? 5550 : len;
		len -= tlen;
		do {
			a += *buf++;
			b += a;
		} while (--tlen);
		a = (a & 0xffff) + (a >> 16) * (65536 - 65521);
		b = (b & 0xffff) + (b >> 16) * (65536 - 65521);
	}
	if (a >= 65521)
		a -= 65521;

	b = (b & 0xffff) + (b >> 16) * (65536 - 65521);
	if (b >= 65521)
		b -= 65521;


	return (b << 16) | a;
}

ADLER32::ADLER32() {}

ADLER32::~ADLER32() {}