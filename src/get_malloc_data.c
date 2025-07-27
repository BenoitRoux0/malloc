#include <malloc.h>

static size_t	count_arenas(t_arena_hdr* arena);

t_malloc_data	get_malloc_data(void) {
	t_malloc_data data;

	data.mmaped_tiny = count_arenas(g_arenas.tiny);
	data.mmaped_small = count_arenas(g_arenas.small);

	return data;
}

static size_t	count_arenas(t_arena_hdr* arena) {
	size_t count = 0;

	while (arena) {
		arena = arena->next;
		++count;
	}

	return count;
}
