#include "malloc.h"

void	free_large(void* chunk_ptr) {
	lock_alloc();

	t_arena_hdr*	arena_hdr = chunk_ptr - sizeof(t_arena_hdr);

	unlock_alloc();

	remove_arena(&g_arenas.large, arena_hdr);
}
