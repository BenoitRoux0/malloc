#include <strings.h>

#include "malloc.h"

void*	realloc(void* ptr, size_t size) {
#ifdef DEBUG
	put_str(2, "realloc: ");
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, "\n");
#endif


	if (ptr == NULL) {
		return malloc(size);
	}

	if (size == 0) {
		free(ptr);
		return NULL;
	}

	t_chunk_header*	chunk_header = ptr - sizeof(t_chunk_header);

	if (size >= chunk_header->size && size <= chunk_header->true_size) {
		chunk_header->size = size;
		return ptr;
	}

	// size_t old_size = chunk_header->size;

	void*	new_ptr = NULL;

	if (size <= TINY_MAX) {
#ifdef DEBUG
		put_str(2, "realloc to tiny\n");
#endif
		new_ptr = to_tiny(chunk_header, size);
	} else if (size <= SMALL_MAX) {
#ifdef DEBUG
		put_str(2, "realloc to small\n");
#endif
		new_ptr = to_small(chunk_header, size);
	} else {
#ifdef DEBUG
		put_str(2, "realloc to large\n");
#endif
		new_ptr = to_large(chunk_header, size);
	}

#ifdef DEBUG
	put_str(2, "got new ptr\n");
#endif

	// if (size > old_size) {
	// 	bzero(new_ptr + old_size, size - old_size - 1);
	// }

#ifdef DEBUG
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, " realloc'd\n");
#endif

	return new_ptr;
}
