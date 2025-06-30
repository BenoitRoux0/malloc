#include "malloc.h"

static void	put_tiny_arena(t_arena_hdr* arena);
static void	put_small_arena(t_arena_hdr* arena);
static void	put_large_arena(t_arena_hdr* arena);
static bool ptrcmp(void* a, void* b);

void	show_alloc_mem(void) {
	t_arena_hdr*	tiny_arena = g_arenas.tiny;
	t_arena_hdr*	small_arena = g_arenas.small;
	t_arena_hdr*	large_arena = g_arenas.large;

	while (tiny_arena != NULL || small_arena != NULL || large_arena != NULL) {
		if (ptrcmp(tiny_arena, small_arena) && ptrcmp(tiny_arena, large_arena)) {
			put_tiny_arena(tiny_arena);
			tiny_arena = tiny_arena->next;
		}

		if (ptrcmp(small_arena, tiny_arena) && ptrcmp(small_arena, large_arena)) {
			put_small_arena(small_arena);
			small_arena = small_arena->next;
		}

		if (ptrcmp(large_arena, tiny_arena) && ptrcmp(large_arena, small_arena)) {
			put_large_arena(large_arena);
			large_arena = large_arena->next;
		}
	}
}

static bool ptrcmp(void* a, void* b) {
	if (!a)
		return b;

	if (!b)
		return a;

	return a < b;
}

static void	put_tiny_arena(t_arena_hdr* arena) {
	put_str(1, "TINY: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");
}

static void	put_small_arena(t_arena_hdr* arena) {
	put_str(1, "SMALL: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");
}

static void	put_large_arena(t_arena_hdr* arena) {
	put_str(1, "LARGE: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");
}
