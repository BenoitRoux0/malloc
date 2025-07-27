#include "malloc.h"

size_t min(size_t x, size_t y) {
	if (x < y)
		return x;

	return y;
}