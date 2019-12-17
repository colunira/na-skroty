#include "crc32.h"
#include <stddef.h>
#include <stdint.h>

uint32_t CRC32::crc32(uint32_t in, unsigned char *buf, size_t len) {
	const uint32_t Polynomial = 0xEDB88320;
	uint32_t crc = 0xFFFFFFFF ^ in;
	unsigned char* current = (unsigned char*)buf;
	while (len--)
	{
		crc ^= *current++;
		for (unsigned int j = 0; j < 8; j++)
			if (crc & 1)
				crc = (crc >> 1) ^ Polynomial;
			else
				crc = crc >> 1;
	}
	return ~crc; 
}

CRC32::CRC32() {}

CRC32::~CRC32() {}