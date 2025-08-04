#include "malloc.h"

void*	to_large(t_chunk_header* chunk_header, size_t size) {
	if (get_size_category(chunk_header->true_size) == LARGE && size <= chunk_header->true_size) {
		chunk_header->size = size;
		return (void*) chunk_header + sizeof(t_chunk_header);
	}

	uint8_t* new_ptr = alloc_large(size);
	t_chunk_header* new_chunk = (void*) new_ptr - sizeof(t_chunk_header);

	if (!new_ptr)
		return NULL;

	void*	old_ptr = (void*)chunk_header + sizeof(t_chunk_header);
	size_t	copy_size = min(chunk_header->true_size, new_chunk->true_size);

	if (get_size_category(chunk_header->size) == TINY)
		copy_size = TINY_MAX;

	ft_memmove(new_ptr, old_ptr, copy_size);

	free_chunk(chunk_header);
	return new_ptr;
}
