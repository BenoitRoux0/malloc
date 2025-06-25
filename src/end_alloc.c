#include "malloc.h"

void	end_alloc(void) {
	t_arena_hdr*	current;
	t_arena_hdr*	next;

	put_str(1, "end alloc\n");

	current = g_arenas.tiny;

	while (current) {
		next = current->next;
		put_str(1, "unmap arena tiny\n");
		munmap(current, current->size);
		current = next;
	}

	current = g_arenas.small;

	while (current) {
		next = current->next;
		put_str(1, "unmap arena small\n");
		munmap(current, current->size);
		current = next;
	}

	current = g_arenas.large;

	while (current) {
		next = current->next;
		put_str(1, "unmap arena large\n");
		munmap(current, current->size);
		current = next;
	}
}
