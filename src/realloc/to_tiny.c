#include "malloc.h"

void*	to_tiny(t_chunk_header* chunk_header, size_t size) {
	if (get_size_category(chunk_header->size) == TINY) {
		chunk_header->size = size;
		return (void*) chunk_header + sizeof(t_chunk_header);
	}

	uint8_t* new_ptr = alloc_tiny(size);

	if (!new_ptr) {
		put_str(2, "tiny failed\n");
		return NULL;
	}

	uint8_t* old_ptr = (void*) chunk_header + sizeof(t_chunk_header);

	ft_memmove(new_ptr, old_ptr, TINY_MAX);

	free_chunk(chunk_header);
	return new_ptr;
}
