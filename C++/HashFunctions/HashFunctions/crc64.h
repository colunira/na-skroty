#pragma once
#include <stdint.h>



class CRC64
{
public:
	CRC64();
	~CRC64();
	uint64_t CRC64::crc64_ecma182(uint64_t crc, unsigned char *buf, size_t len);
};