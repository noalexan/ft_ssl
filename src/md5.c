#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__uint8_t *md5(const __uint8_t *message, __uint64_t message_length, __uint8_t *digest)
{
	// Allocate new array with size divisible by 512bits
	__uint64_t data_length = ((message_length + 7) / 64 + 1) * 64;
	__uint8_t *data = malloc(data_length);

	if (data == NULL) {
		perror("malloc");
		return NULL;
	}

	// Copy original message into data
	memcpy(data, message, message_length);

	// Padding to fill remaining bits
	if ((message_length + 8) % 64) {
		data[message_length] = 0b10000000;
		for (__uint64_t i = message_length + 1; i < data_length - 8; i++)
			data[i] = 0;
	}

	// Replace 8 end bytes by original message size
	((__uint64_t *)data)[data_length / 8 - 1] = message_length;

	// Iterate on all 512bits blocks
	for (__uint64_t i = 0; i < data_length; i += 64) {
		write(1, data + i, 64);
	}

	(void)digest;

	free(data);
	return NULL;
}
