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

#ifdef DEBUG
	if (ptr == NULL) {
		put_str(2, "calloc returned NULL\n");
	} else {
		put_str(2, "calloc returned ");
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, "\n");
	}
#endif

	if (!ptr)
		return NULL;

	for (size_t i = 0; i < total_size; ++i) {
		ptr[i] = 0;
	}

	return ptr;
}