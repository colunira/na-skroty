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
	string md5(const unsigned char* input, size_t inputLen);

#ifndef SAMPLE_TEST
private:
#endif
	void init();
	void transform(const uint8_t block[BLOCK_SIZE]);

	uint8_t buffer[BLOCK_SIZE]; 
	uint8_t digest[16]; 

	uint32_t state[4];  
	uint32_t lo, hi;   
	bool finalized; 
};

string md5(const string str);

