#include "malloc.h"

void	free_tiny(void* chunk_ptr);
void	free_small(void* chunk_ptr);
void	free_large(void* chunk_ptr);

/**
 * @brief Free the allocated memory
 * @param ptr The pointer to memory to be freed
 */
void	free(void *ptr) {
#ifdef DEBUG
	put_str(2, "free: ");
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, "\n");
#endif

	if (ptr == NULL)
		return;

	t_chunk_header*	chunk_header = ptr - sizeof(t_chunk_header);

	if (!chunk_header->owned)
		return;

	if (chunk_header->size <= TINY_MAX) {
		free_tiny(chunk_header);
#ifdef DEBUG
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, " freed");
		put_str(2, "\n");
#endif
		return;
	}

	if (chunk_header->size <= SMALL_MAX) {
		free_small(chunk_header);
#ifdef DEBUG
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, " freed");
		put_str(2, "\n");
#endif
		return;
	}

	free_large(chunk_header);

#ifdef DEBUG
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, " freed");
	put_str(2, "\n");
#endif
}

void	free_large(void* chunk_ptr) {
	lock_alloc();

	t_arena_hdr*	arena_hdr = chunk_ptr - sizeof(t_arena_hdr);

	unlock_alloc();

	remove_arena(&g_arenas.large, arena_hdr);
}

void	free_small(void* chunk_ptr) {
	lock_alloc();

	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = get_main_arena(chunk_hdr);

	if (arena_hdr == NULL)
		return;

	chunk_hdr->owned = false;

	if ((void*) get_next_chunk(chunk_hdr) < get_border_addr(chunk_hdr)) {
		if (!get_next_chunk(chunk_hdr)->owned) {
			chunk_hdr->true_size += get_next_chunk(chunk_hdr)->true_size + sizeof(t_chunk_header);
		}
	}

	if (chunk_hdr->prec_chunk && !chunk_hdr->prec_chunk->owned) {
		chunk_hdr->prec_chunk->true_size += chunk_hdr->true_size + sizeof(t_chunk_header);
	}

	--arena_hdr->allocated;
	if (arena_hdr->allocated == 0) {
		update_after_free_small();
	}

	unlock_alloc();
}

void	free_tiny(void* chunk_ptr) {
	lock_alloc();

	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = get_main_arena(chunk_hdr);

	if (arena_hdr == NULL)
		return;

#ifdef DEBUG
	put_str(2, "tiny arena: ");
	put_ptr(2, (uintptr_t) arena_hdr);
	put_str(2, "\n");
#endif

	chunk_hdr->owned = false;
	--arena_hdr->allocated;

	if (arena_hdr->allocated == 0) {
		update_after_free_tiny();
	}

	unlock_alloc();
}
