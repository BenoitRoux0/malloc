#include "malloc.h"

size_t	get_chunk_size(const void* chunk) {
	const t_chunk_header*	header = chunk;

	if (header->size % 16 == 0)
		return header->size;

	return header->size + (16 - header->size % 16);
}
