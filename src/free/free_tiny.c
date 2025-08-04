#include "malloc.h"

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
