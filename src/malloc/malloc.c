#include "malloc.h"

t_arenas g_arenas = {
	0,
	0,
	NULL,
	0,
	NULL,
	NULL
};

#ifdef BONUS
pthread_mutex_t	g_alloc_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

void*	malloc(size_t size) {
	if (g_arenas.page_size == 0) {
		g_arenas.page_size = sysconf(_SC_PAGESIZE);
		g_arenas.tiny_arena_size = g_arenas.page_size * TINY_ARENA_SIZE;
		g_arenas.small_arena_size = g_arenas.page_size * SMALL_ARENA_SIZE;
	}

#ifdef DEBUG
	put_str(2, "malloc: ");
	put_nbr(2, (uintptr_t) size);
	put_str(2, "\n");
#endif

	void*	ptr;

	if (size <= TINY_MAX) {
		ptr = alloc_tiny(size);
	} else if (size <= SMALL_MAX) {
		ptr = alloc_small(size, NULL);
	} else {
		ptr = alloc_large(size);
	}

#ifdef DEBUG
	if (ptr == NULL) {
		put_str(2, "malloc returned NULL\n");
	}

	if (ptr) {
		put_str(2, "malloc returned ");
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, "\n");
	}
#endif

	return ptr;
}
