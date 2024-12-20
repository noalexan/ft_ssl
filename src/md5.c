#include <endian.h>
#include <md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

const uint32_t s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

struct __attribute__((packed)) s_md5_ctx {
	uint32_t a0;
	uint32_t b0;
	uint32_t c0;
	uint32_t d0;
};

uint8_t *md5(const uint8_t *message, uint64_t message_length, uint8_t *digest)
{
	// Allocate new array with size divisible by 512bits
	uint64_t data_length = ((message_length + 8) / MD5_BLOCK_LENGTH + 1) * MD5_BLOCK_LENGTH;
	uint8_t *data = malloc(data_length);

	if (data == NULL) {
		perror("malloc");
		return NULL;
	}

	// Copy original message into data
	memcpy(data, message, message_length);
	data[message_length] = 0b10000000;

	// Padding to fill remaining bits
	if ((message_length + 9) % MD5_BLOCK_LENGTH)
		for (uint64_t i = message_length + 1; i < data_length - 9; i++)
			data[i] = 0;

	// Replace 8 end bytes by original message size
	((uint64_t *)data)[data_length / 8 - 1] = htole64(message_length * 8);

	struct s_md5_ctx ctx;

	ctx.a0 = 0x67452301;
	ctx.b0 = 0xefcdab89;
	ctx.c0 = 0x98badcfe;
	ctx.d0 = 0x10325476;

	// Iterate on all 512bits blocks
	for (uint32_t *M = (uint32_t *)data; (uint8_t *)M - (uint8_t *)data < (ssize_t)data_length; M += 16) {
		uint32_t A = ctx.a0;
		uint32_t B = ctx.b0;
		uint32_t C = ctx.c0;
		uint32_t D = ctx.d0;

		for (uint32_t i = 0; i < 64; i++) {
			uint32_t F, g;

			if (i <= 15) {
				F = (B & C) | (~B & D);
				g = i;
			} else if (16 <= i && i <= 31) {
				F = (D & B) | (~D & C);
				g = (5 * i + 1) % 16;
			} else if (32 <= i && i <= 47) {
				F = B ^ C ^ D;
				g = (3 * i + 5) % 16;
			} else if (48 <= i && i <= 63) {
				F = C ^ (B | ~D);
				g = (7 * i) % 16;
			}

			F = F + A + K[i] + M[g];
			A = D;
			D = C;
			C = B;
			B = B + leftrotate(F, s[i]);
		}

		ctx.a0 += A;
		ctx.b0 += B;
		ctx.c0 += C;
		ctx.d0 += D;
	}

	for (uint8_t *i = (uint8_t *)&ctx; i - (uint8_t *)&ctx < MD5_DIGEST_LENGTH; i++) {
		sprintf((char *)digest + (i - (uint8_t *)&ctx) * 2, "%.2x", *i);
	}

	free(data);
	return NULL;
}
