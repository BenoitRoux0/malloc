#include "malloc.h"

static size_t	put_tiny_arena(int fd, void* arena);
static size_t	put_small_arena(int fd, void* arena);
static size_t	put_large_arena(int fd, void* arena);
static bool		ptrcmp(void* a, void* b);

void	show_alloc_mem_fd(int fd, bool show_tiny, bool show_small, bool show_large) {
	t_arena_hdr*	tiny_arena = g_arenas.tiny;
	t_arena_hdr*	small_arena = g_arenas.small;
	t_arena_hdr*	large_arena = g_arenas.large;
	size_t			total = 0;

	if (!show_tiny)
		tiny_arena = NULL;

	if (!show_small)
		small_arena = NULL;

	if (!show_large)
		large_arena = NULL;

	while (tiny_arena != NULL || small_arena != NULL || large_arena != NULL) {
		if (tiny_arena && ptrcmp(tiny_arena, small_arena) && ptrcmp(tiny_arena, large_arena)) {
			total += put_tiny_arena(fd, tiny_arena);
			tiny_arena = tiny_arena->next;
		}

		if (small_arena && ptrcmp(small_arena, tiny_arena) && ptrcmp(small_arena, large_arena)) {
			total += put_small_arena(fd, small_arena);
			small_arena = small_arena->next;
		}

		if (large_arena && ptrcmp(large_arena, tiny_arena) && ptrcmp(large_arena, small_arena)) {
			total += put_large_arena(fd, large_arena);
			large_arena = large_arena->next;
		}
	}

	put_str(fd , "Total : ");
	put_nbr(fd , total);
	put_str(fd , " bytes\n");
}

static bool ptrcmp(void* a, void* b) {
	if (!a)
		return b;

	if (!b)
		return a;

	return a < b;
}

static size_t	put_tiny_arena(int fd, void* arena) {
	put_str(fd, "TINY: 0x");
	put_hexa(fd, (size_t) arena);
	put_str(fd, "\n");

	size_t	total = 0;

	for (void* chunk_ite = arena + sizeof(t_arena_hdr); chunk_ite < (arena + g_arenas.tiny_arena_size); chunk_ite += (sizeof(t_chunk_header) + TINY_MAX)) {
		if (has_chunk(chunk_ite)->owned) {
			put_ptr(fd, (size_t) chunk_ite + sizeof(t_chunk_header));
			put_str(fd, " - ");
			put_ptr(fd, (size_t) chunk_ite + sizeof(t_chunk_header) + has_chunk(chunk_ite)->size);
			put_str(fd, " : ");
			put_nbr(fd, has_chunk(chunk_ite)->size);
			put_str(fd, " bytes\n");
			total += has_chunk(chunk_ite)->size;
		}
	}

	return total;
}

static size_t	put_small_arena(int fd, void* arena) {
	put_str(fd , "SMALL: 0x");
	put_hexa(fd , (size_t) arena);
	put_str(fd , "\n");

	size_t	total = 0;

	for (void* chunk_ite = arena + sizeof(t_arena_hdr); chunk_ite < arena + g_arenas.small_arena_size; chunk_ite = get_next_chunk(chunk_ite)) {
		if (has_chunk(chunk_ite)->owned) {
			put_ptr(fd , (size_t) chunk_ite + sizeof(t_chunk_header));
			put_str(fd , " - ");
			put_ptr(fd , (size_t) chunk_ite + sizeof(t_chunk_header) + has_chunk(chunk_ite)->size);
			put_str(fd , " : ");
			put_nbr(fd , has_chunk(chunk_ite)->size);
			put_str(fd , " bytes\n");
			total += has_chunk(chunk_ite)->size;
		}
	}

	return total;
}

static size_t	put_large_arena(int fd, void* arena) {
	put_str(fd , "LARGE: 0x");
	put_hexa(fd , (size_t) arena);
	put_str(fd , "\n");

	void* chunk = arena + sizeof(t_arena_hdr);

	if (has_chunk(chunk)->owned) {
		put_ptr(fd , (size_t) chunk + sizeof(t_chunk_header));
		put_str(fd , " - ");
		put_ptr(fd , (size_t) chunk + sizeof(t_chunk_header) + has_chunk(chunk)->size);
		put_str(fd , " : ");
		put_nbr(fd , has_chunk(chunk)->size);
		put_str(fd , " bytes\n");
	}

	return has_chunk(chunk)->size;
}
