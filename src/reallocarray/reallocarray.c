#include "malloc.h"

void*	reallocarray(void* ptr, size_t nmemb, size_t size) {
	size_t	total_size = nmemb * size;

	if (total_size / size != nmemb)
		return NULL;

	return realloc(ptr, total_size);
}