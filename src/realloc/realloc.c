#include "malloc.h"

static void*	to_tiny(t_chunk_header* chunk_header, size_t size);
static void*	to_small(t_chunk_header* chunk_header, size_t size);
static void*	to_large(t_chunk_header* chunk_header, size_t size);

void*	realloc(void* ptr, size_t size) {
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

	if (size <= TINY_MAX) {
		return to_tiny(chunk_header, size);
	}

	if (size <= SMALL_MAX) {
		return to_small(chunk_header, size);
	}

	return to_large(chunk_header, size);
}

static void*	to_tiny(t_chunk_header* chunk_header, size_t size) {
	(void) chunk_header;
	(void) size;
	return NULL;
}

static void*	to_small(t_chunk_header* chunk_header, size_t size) {
	(void) chunk_header;
	(void) size;
	return NULL;
}

static void*	to_large(t_chunk_header* chunk_header, size_t size) {
	uint8_t* new_ptr = alloc_large(size);
	t_chunk_header* new_chunk = (void*) new_ptr - sizeof(t_chunk_header);

	if (!new_ptr)
		return NULL;

	uint8_t* old_ptr = ((void*) chunk_header) + sizeof(t_chunk_header);
	size_t	copy_size = min(chunk_header->size, new_chunk->size);

	for (size_t i = 0; i < copy_size; ++i) {
		new_ptr[i] = old_ptr[i];
	}

	free(old_ptr);
	return new_ptr;
}
