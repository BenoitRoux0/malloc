#include "malloc.h"

void*	alloc_tiny(size_t size) {
	void*	ptr = take_tiny(size);

	return ptr + sizeof (t_chunk_header);
}
