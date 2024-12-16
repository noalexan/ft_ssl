#pragma once

#include <stddef.h>

#define MD5_DIGEST_LENGTH 32

/*
 * ### Message-Digest 5 (MD5) hashing algorithm function
 * Compute `message` to create a hash and
 * save it in the `digest` pointer
 */
__uint8_t *md5(const __uint8_t *message, __uint64_t message_length, __uint8_t *digest);
