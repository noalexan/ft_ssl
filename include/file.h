#pragma once

#include <stddef.h>

#define BUFFER_SIZE 512

typedef struct s_file {
	char *content;
	size_t length;
} file;

file *load_file(const int fd);
