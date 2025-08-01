#include "malloc.h"

void*	calloc(size_t nmemb, size_t size) {
#ifdef DEBUG
	put_str(2, "calloc: ");
	put_nbr(2, nmemb);
	put_str(2, " * ");
	put_nbr(2, size);
	put_str(2, "\n");
#endif

	size_t	total_size = nmemb * size;

	if (total_size / size != nmemb)
		return NULL;

	uint8_t*	ptr = malloc(total_size);

	if (!ptr)
		return NULL;

	for (size_t i = 0; i < total_size; ++i) {
		ptr[i] = 0;
	}

	return ptr;
}