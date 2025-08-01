#include "malloc.h"

void*	ft_memmove(void* dst, const void* src, size_t len) {
	const unsigned char	*from;
	unsigned char		*to;

	from = (const unsigned char *) src;
	to = (unsigned char *) dst;
	if (from < to && to - from < (int) len) {
		for (size_t i = len; i > 0; --i)
			to[i - 1] = from[i - 1];
	} else {
		return ft_memcpy(dst, src, len);
	}

	return dst;
}
