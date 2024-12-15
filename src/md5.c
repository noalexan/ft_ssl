#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned char *md5(const unsigned char *message, size_t message_length)
{
	unsigned char *data = malloc(((message_length - 1) / 64 + 1) * 64);
	memcpy(data, message, message_length);

	if (message_length % 64) {
		data[message_length] = 0b10000000;
		for (size_t i = message_length + 1; i % 64; i++) {
			data[i] = 0;
		}
	}

	for (size_t i = 0; i < message_length; i += 64) {
		write(1, &(data[i]), 64);
	}

	return data;
}
