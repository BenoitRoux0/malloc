#include "malloc.h"

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