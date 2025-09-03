#include "malloc.h"

void	free_large(void* chunk_ptr) {
	t_arena_hdr*	arena_hdr = chunk_ptr - sizeof(t_arena_hdr);

	lock_alloc();

#ifdef DEBUG
	put_str(2, "unmap large arena\n");
#endif
	remove_arena(&g_arenas.large, arena_hdr);

	unlock_alloc();
}
