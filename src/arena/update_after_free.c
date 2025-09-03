#include "malloc.h"

static size_t	count_allocated_tiny(void* arena);

void	update_after_free_tiny(void) {
	bool	found_empty = false;

	for (t_arena_hdr* arena = g_arenas.tiny; arena != NULL; arena = arena->next) {
		arena->allocated = count_allocated_tiny(arena);
		if (arena->allocated != 0) continue;

		if (!found_empty) {
			found_empty = true;
			continue;
		}
#ifdef DEBUG
		put_str(2, "unmap tiny arena\n");
#endif
		remove_arena(&g_arenas.tiny, arena);
		return;
	}
}

void	update_after_free_small(void) {
	bool	found_empty = false;

	for (t_arena_hdr* arena = g_arenas.small; arena != NULL; arena = arena->next) {
		if (arena->allocated != 0) continue;

		if (!found_empty) {
			found_empty = true;
			continue;
		}
#ifdef DEBUG
		put_str(2, "unmap small arena\n");
#endif
		remove_arena(&g_arenas.small, arena);
		return;
	}
}

void	remove_arena(t_arena_hdr** target, t_arena_hdr* to_remove) {
	if (!target || !*target || !to_remove)
		return;

	if (*target == to_remove) {
		*target = to_remove->next;
#ifdef DEBUG
		put_str(2, "unmap arena\n");
#endif
		munmap(to_remove, to_remove->size);
		return;
	}

	remove_arena(&(*target)->next, to_remove);
}

static size_t	count_allocated_tiny(void* arena) {
	size_t	count = 0;

	for (void* chunk_ite = arena + sizeof(t_arena_hdr); chunk_ite < (arena + g_arenas.tiny_arena_size); chunk_ite += (sizeof(t_chunk_header) + TINY_MAX)) {
		if (has_chunk(chunk_ite)->owned) {
			++count;
		}
	}

	return count;
}
