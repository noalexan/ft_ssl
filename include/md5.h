#pragma once

#include <stdint.h>

#define MD5_BLOCK_LENGTH 64
#define MD5_DIGEST_LENGTH 16
#define MD5_DIGEST_STRING_LENGTH MD5_DIGEST_LENGTH * 2 + 1

/*
 * ### Message-Digest 5 (MD5) hashing algorithm function
 * Compute `message` to create a hash and
 * save it in the `digest` pointer
 */
uint8_t *md5(const uint8_t *message, uint64_t message_length, uint8_t *digest);
