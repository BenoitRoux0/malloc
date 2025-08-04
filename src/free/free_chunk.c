#include "malloc.h"

void	free_chunk(t_chunk_header* chunk_ptr) {
	if (chunk_ptr->size <= TINY_MAX) {
		free_tiny(chunk_ptr);
		return;
	}

	if (chunk_ptr->size <= SMALL_MAX) {
		free_small(chunk_ptr);
		return;
	}

	free_large(chunk_ptr);
}
