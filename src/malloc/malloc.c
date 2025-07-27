#include "malloc.h"

t_arenas g_arenas = {
	0,
	0,
	NULL,
	0,
	NULL,
	NULL
};

void*	malloc(size_t size) {
	if (g_arenas.page_size == 0) {
		g_arenas.page_size = sysconf(_SC_PAGESIZE);
		g_arenas.tiny_arena_size = g_arenas.page_size * TINY_ARENA_SIZE;
		g_arenas.small_arena_size = g_arenas.page_size * SMALL_ARENA_SIZE;
	}

	if (size <= TINY_MAX) {
		return alloc_tiny(size);
	}

	if (size <= SMALL_MAX) {
		return alloc_small(size);
	}

	return alloc_large(size);
}
