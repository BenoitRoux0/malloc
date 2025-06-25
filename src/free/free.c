#include "malloc.h"

void	free_tiny(void* chunk_ptr);
void	free_small(void* chunk_ptr);
void	free_large(void* chunk_ptr);

void	free(void *ptr) {
	if (ptr == NULL)
		return;

	t_chunk_header*	chunk_header = ptr - sizeof(t_chunk_header);

	if (!chunk_header->owned)
		return;

	if (chunk_header->size <= TINY_MAX) {
		free_tiny(chunk_header);
		return;
	}

	if (chunk_header->size <= SMALL_MAX) {
		free_small(chunk_header);
		return;
	}

	free_large(chunk_header);
}

void	free_large(void* chunk_ptr) {
	t_arena_hdr*	arena_hdr = chunk_ptr - sizeof(t_arena_hdr);

	remove_arena(&g_arenas.large, arena_hdr);
}

void	free_small(void* chunk_ptr) {
	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = chunk_ptr - chunk_hdr->offset;

	chunk_hdr->owned = false;
	--arena_hdr->allocated;
}

void	free_tiny(void* chunk_ptr) {
	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = chunk_ptr - chunk_hdr->offset;

	chunk_hdr->owned = false;
	--arena_hdr->allocated;

	if (arena_hdr->allocated == 0) {
		update_after_free_tiny();
	}
}
