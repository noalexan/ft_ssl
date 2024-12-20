#include <stdint.h>

uint32_t leftrotate(uint32_t a, uint32_t b)
{
	for (uint32_t i = 0; i < b; i++) {
		a = (a >> 31) | (a << 1);
	}
	return a;
}
