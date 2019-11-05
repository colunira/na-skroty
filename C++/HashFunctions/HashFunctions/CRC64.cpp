
#include "crc64.h"
#include <stddef.h>
#include <stdint.h>

#define POLY UINT64_C(0x42f0e1eba9ea3693)
#define TOP UINT64_C(0x8000000000000000)

int64_t CRC64::crc64_ecma182(int64_t crc, unsigned char *buf, size_t len)
{
	int k;

	if (buf == NULL)
		return 0;
	while (len--) {
		crc ^= (uint64_t)(*buf++) << 56;
		for (k = 0; k < 8; k++)
			crc = crc & TOP ? (crc << 1) ^ POLY : crc << 1;
	}
	return crc;
}

CRC64::CRC64() {}

CRC64::~CRC64() {}