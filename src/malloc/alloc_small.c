#include "malloc.h"

void*	alloc_small(size_t size) {
	void*	ptr = take_small(size);

	return ptr + sizeof (t_chunk_header);
}
