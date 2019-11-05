#pragma once
#include <stdint.h>

class CRC64
{
public:
	CRC64();
	~CRC64();
	int64_t CRC64::crc64_ecma182(int64_t crc, unsigned char *buf, size_t len);
};