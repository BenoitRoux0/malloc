#include "malloc.h"

static size_t	put_tiny_arena(void* arena);
static size_t	put_small_arena(void* arena);
static size_t	put_large_arena(void* arena);
static bool		ptrcmp(void* a, void* b);

void	show_alloc_mem(void) {
	t_arena_hdr*	tiny_arena = g_arenas.tiny;
	t_arena_hdr*	small_arena = g_arenas.small;
	t_arena_hdr*	large_arena = g_arenas.large;
	size_t			total = 0;

	while (tiny_arena != NULL || small_arena != NULL || large_arena != NULL) {
		if (tiny_arena && ptrcmp(tiny_arena, small_arena) && ptrcmp(tiny_arena, large_arena)) {
			total += put_tiny_arena(tiny_arena);
			tiny_arena = tiny_arena->next;
		}

		if (small_arena && ptrcmp(small_arena, tiny_arena) && ptrcmp(small_arena, large_arena)) {
			total += put_small_arena(small_arena);
			small_arena = small_arena->next;
		}

		if (large_arena && ptrcmp(large_arena, tiny_arena) && ptrcmp(large_arena, small_arena)) {
			total += put_large_arena(large_arena);
			large_arena = large_arena->next;
		}
	}

	put_str(1, "Total : ");
	put_nbr(1, total);
	put_str(1, " bytes\n");
}

static bool ptrcmp(void* a, void* b) {
	if (!a)
		return b;

	if (!b)
		return a;

	return a < b;
}

static size_t	put_tiny_arena(void* arena) {
	put_str(1, "TINY: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");

	size_t	total = 0;

	for (void* chunk_ite = arena + sizeof(t_arena_hdr); chunk_ite < (arena + g_arenas.tiny_arena_size); chunk_ite += (sizeof(t_chunk_header) + TINY_MAX)) {
		if (has_chunk(chunk_ite)->owned) {
			put_ptr(1, (size_t) chunk_ite + sizeof(t_chunk_header));
			put_str(1, " - ");
			put_ptr(1, (size_t) chunk_ite + sizeof(t_chunk_header) + has_chunk(chunk_ite)->size);
			put_str(1, " : ");
			put_nbr(1, has_chunk(chunk_ite)->size);
			put_str(1, " bytes\n");
			total += has_chunk(chunk_ite)->size;
		}
	}

	return total;
}

static size_t	put_small_arena(void* arena) {
	put_str(1, "SMALL: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");

	size_t	total = 0;

	for (void* chunk_ite = arena + sizeof(t_arena_hdr); chunk_ite < arena + g_arenas.small_arena_size; chunk_ite = get_next_chunk(chunk_ite)) {
		if (has_chunk(chunk_ite)->owned) {
			put_ptr(1, (size_t) chunk_ite + sizeof(t_chunk_header));
			put_str(1, " - ");
			put_ptr(1, (size_t) chunk_ite + sizeof(t_chunk_header) + has_chunk(chunk_ite)->size);
			put_str(1, " : ");
			put_nbr(1, has_chunk(chunk_ite)->size);
			put_str(1, " bytes\n");
			total += has_chunk(chunk_ite)->size;
		}
	}

	return total;
}

static size_t	put_large_arena(void* arena) {
	put_str(1, "LARGE: 0x");
	put_hexa(1, (size_t) arena);
	put_str(1, "\n");

	void* chunk = arena + sizeof(t_arena_hdr);

	if (has_chunk(chunk)->owned) {
		put_ptr(1, (size_t) chunk + sizeof(t_chunk_header));
		put_str(1, " - ");
		put_ptr(1, (size_t) chunk + sizeof(t_chunk_header) + has_chunk(chunk)->size);
		put_str(1, " : ");
		put_nbr(1, has_chunk(chunk)->size);
		put_str(1, " bytes\n");
	}

	return has_chunk(chunk)->size;
}
