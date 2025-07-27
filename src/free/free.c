#include "malloc.h"

void	free_tiny(void* chunk_ptr);
void	free_small(void* chunk_ptr);
void	free_large(void* chunk_ptr);

/**
 * @brief Free the alloc'd memory
 * @param ptr The pointer to memory to be freed
 */
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
	t_arena_hdr*	arena_hdr = get_main_arena(chunk_hdr);

	chunk_hdr->owned = false;

	if ((void*) get_next_chunk(chunk_hdr) < get_border_addr(chunk_hdr)) {
		if (!get_next_chunk(chunk_hdr)->owned) {
			chunk_hdr->true_size += get_next_chunk(chunk_hdr)->true_size;
		}
	}

	if (chunk_hdr->prec_chunk && !chunk_hdr->prec_chunk->owned) {
		chunk_hdr->prec_chunk->true_size += chunk_hdr->true_size;
	}

	--arena_hdr->allocated;
	if (arena_hdr->allocated == 0) {
		update_after_free_small();
	}
}

void	free_tiny(void* chunk_ptr) {
	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = get_main_arena(chunk_hdr);

	chunk_hdr->owned = false;
	--arena_hdr->allocated;

	if (arena_hdr->allocated == 0) {
		update_after_free_tiny();
	}
}
