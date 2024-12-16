#include <file.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

file *load_file(const int fd)
{
	file *f;
	unsigned char buffer[BUFFER_SIZE];

	f = calloc(1, sizeof(file));
	if (f == NULL) {
		perror("calloc");
		return NULL;
	}

	f->content = malloc(1);
	if (f->content == NULL) {
		perror("malloc");
		free(f);
		return NULL;
	}
	*f->content = 0;

	while (true) {
		ssize_t val = read(fd, buffer, sizeof(buffer));

		if (val < 0) {
			perror("read");
			return NULL;
		}

		if (val == 0)
			break;

		f->content = realloc(f->content, f->length + val);

		if (f->content == NULL) {
			perror("realloc");
			free(f);
			return NULL;
		}

		memcpy(f->content + f->length, buffer, val);
		f->length += val;
	}

	return f;
}