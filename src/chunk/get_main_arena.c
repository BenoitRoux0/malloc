#include "malloc.h"

t_arena_hdr*	get_main_arena(void* chunk) {
	void* arena_ptr = chunk - (uintptr_t)chunk % g_arenas.page_size;

	while (!has_arena(arena_ptr)->is_main) {
		arena_ptr -= g_arenas.page_size;
	}

	return arena_ptr;
}
