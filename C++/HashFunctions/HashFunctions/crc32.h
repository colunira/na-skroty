#pragma once
#include <stdint.h>

class CRC32
{
public:
	CRC32();
	~CRC32();
	uint32_t CRC32::crc32(uint32_t crc, unsigned char *buf, size_t len);
};