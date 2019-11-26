#pragma once

#include <stddef.h>
#define MD2_BLOCK_SIZE 16

typedef struct {
	unsigned  char data[16];
	unsigned  char state[48];
	unsigned  char checksum[16];
	int len;
} MD2_CTX;

class MD2 {
private:
	void MD2::md2_transform(MD2_CTX *ctx, unsigned  char data[]);
	MD2_CTX md2_ctx;
public:
	void md2_init(MD2_CTX *ctx);
	void md2_update(unsigned char* data, size_t len);
	void md2_final(unsigned char* hash);
	MD2();
};
