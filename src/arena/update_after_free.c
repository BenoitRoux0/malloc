#include "malloc.h"


void	update_after_free_tiny(void) {
	bool	found_empty = false;

	for (t_arena_hdr* arena = g_arenas.tiny; arena != NULL; arena = arena->next) {
		if (arena->allocated == 0) {
			if (!found_empty) {
				found_empty = true;
				continue;
			}
			remove_arena(&g_arenas.tiny, arena);
			return;
		}
	}
}

void	remove_arena(t_arena_hdr** target, t_arena_hdr* to_remove) {
	if (!(*target))
		return;

	if (*target == to_remove) {
		*target = to_remove->next;
		put_str(1, "unmap arena\n");
		munmap(to_remove, to_remove->size);
		return;
	}

	remove_arena(&(*target)->next, to_remove);
}
