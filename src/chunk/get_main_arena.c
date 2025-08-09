#include "malloc.h"

static bool	is_in_arena(void* arena, void* chunk);

t_arena_hdr*	get_main_arena(void* chunk) {
	t_arena_hdr*	arena_hdr;

	arena_hdr = g_arenas.small;

#ifdef DEBUG
	put_str(2, "main arena of ");
	put_ptr(2, (uintptr_t) chunk);
	put_str(2, "\n");
#endif

	while (arena_hdr) {
		if (is_in_arena(arena_hdr, chunk)) {
			return arena_hdr;
		}

		arena_hdr = arena_hdr->next;
	}

	arena_hdr = g_arenas.tiny;

	while (arena_hdr) {
		if (is_in_arena(arena_hdr, chunk)) {
			return arena_hdr;
		}

		arena_hdr = arena_hdr->next;
	}

	arena_hdr = g_arenas.large;

	while (arena_hdr) {
		if (is_in_arena(arena_hdr, chunk)) {
			return arena_hdr;
		}

		arena_hdr = arena_hdr->next;
	}

#ifdef DEBUG
	put_str(2, "main arena is NULL\n");
#endif

	return NULL;
}

static bool	is_in_arena(void* arena, void* chunk) {
	return chunk >= arena && chunk < arena + has_arena(arena)->size;
}
