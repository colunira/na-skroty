#pragma once
#include <cstring>

class MD4 {

public:
	void mdfour(unsigned char *out, const unsigned char *in, int n);
};