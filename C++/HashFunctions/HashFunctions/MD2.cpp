#include <stdlib.h>
#include <memory.h>
#include "MD2.h"

void MD2::md2_transform(MD2_CTX *ctx, BYTE data[])
{
	int j, k, t;

	for (j = 0; j < 16; ++j) {
		ctx->state[j + 16] = data[j];
		ctx->state[j + 32] = (ctx->state[j + 16] ^ ctx->state[j]);
	}

	t = 0;
	for (j = 0; j < 18; ++j) {
		for (k = 0; k < 48; ++k) {
			ctx->state[k] ^= s[t];
			t = ctx->state[k];
		}
		t = (t + j) & 0xFF;
	}

	t = ctx->checksum[15];
	for (j = 0; j < 16; ++j) {
		ctx->checksum[j] ^= s[data[j] ^ t];
		t = ctx->checksum[j];
	}
}

void MD2::md2_init(MD2_CTX *ctx)
{
	int i;

	for (i = 0; i < 48; ++i)
		ctx->state[i] = 0;
	for (i = 0; i < 16; ++i)
		ctx->checksum[i] = 0;
	ctx->len = 0;
}

void MD2::md2_update(MD2_CTX *ctx, const BYTE data[], size_t len)
{
	size_t i;

	for (i = 0; i < len; ++i) {
		ctx->data[ctx->len] = data[i];
		ctx->len++;
		if (ctx->len == MD2_BLOCK_SIZE) {
			md2_transform(ctx, ctx->data);
			ctx->len = 0;
		}
	}
}

void MD2::md2_final(MD2_CTX *ctx, BYTE hash[])
{
	int to_pad;

	to_pad = MD2_BLOCK_SIZE - ctx->len;

	while (ctx->len < MD2_BLOCK_SIZE)
		ctx->data[ctx->len++] = to_pad;

	md2_transform(ctx, ctx->data);
	md2_transform(ctx, ctx->checksum);

	memcpy(hash, ctx->state, MD2_BLOCK_SIZE);
}
