#include <string>
using std::string;

class MD5 {
#define BLOCK_SIZE 64
public:
	MD5();
	MD5& update(const unsigned char* in, size_t inputLen);
	MD5& update(const char* in, size_t inputLen);
	MD5& finalize();
	string toString() const;

#ifndef SAMPLE_TEST
private:
#endif
	void init();
	void transform(const uint8_t block[BLOCK_SIZE]);

	uint8_t buffer[BLOCK_SIZE];  // buffer of the raw data
	uint8_t digest[16];  // result hash, little endian

	uint32_t state[4];  // state (ABCD)
	uint32_t lo, hi;    // number of bits, modulo 2^64 (lsb first)
	bool finalized;  // if the context has been finalized
};

string md5(const string str);

