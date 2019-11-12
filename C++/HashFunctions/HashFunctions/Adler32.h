#pragma once
#include <stdint.h>

class ADLER32
{
public:
	ADLER32();
	~ADLER32();
	uint32_t ADLER32::adler32(uint32_t crc, unsigned char *buf, size_t len);
};