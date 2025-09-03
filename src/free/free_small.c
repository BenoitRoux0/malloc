#include "malloc.h"

void	free_small(void* chunk_ptr) {
	lock_alloc();

	t_chunk_header*	chunk_hdr = chunk_ptr;
	t_arena_hdr*	arena_hdr = get_main_arena(chunk_hdr);

	if (arena_hdr == NULL) {
		unlock_alloc();
		return;
	}

	chunk_hdr->owned = false;

	merge_next_chunk(chunk_hdr);

	t_chunk_header* prec_chunk = chunk_hdr->prec_chunk;

	if (prec_chunk && !prec_chunk->owned)
		merge_next_chunk(prec_chunk);

	--arena_hdr->allocated;
	if (arena_hdr->allocated == 0) {
		update_after_free_small();
	}

#ifdef DEBUG
	if (check_arena(arena_hdr) == false) {
		put_str(2, "problem with coalescing\n");
	} else {
		put_str(2, "coalescing good\n");
	}
#endif

	unlock_alloc();
}