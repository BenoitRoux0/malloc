#include "malloc.h"

void*	ft_memcpy(void *dst, const void *src, size_t n) {
	uint8_t*		dst_ptr = dst;
	const uint8_t*	src_ptr = src;

	for (size_t i = 0; i < n; ++i) {
		dst_ptr[i] = src_ptr[i];
	}

	return dst;
}
