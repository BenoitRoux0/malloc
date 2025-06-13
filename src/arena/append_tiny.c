#include <string.h>

#include "malloc.h"

void*	append_tiny(void) {
	t_arena_hdr*	arena_header;
	void*			ptr;
	t_arena_hdr*	tmp = g_arenas.tiny;

	put_str(1, "mmap arena\n");
	ptr = mmap(NULL, sysconf(_SC_PAGESIZE) * TINY_ARENA_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	arena_header->allocated = 0;
	arena_header->size = sysconf(_SC_PAGESIZE) * TINY_ARENA_SIZE;
	arena_header->next = NULL;

	if (g_arenas.tiny == NULL) {
		g_arenas.tiny = arena_header;
	} else {
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = ptr;
	}

	memset(ptr + sizeof(t_arena_hdr), 0, sysconf(_SC_PAGESIZE) * TINY_ARENA_SIZE - sizeof(t_arena_hdr));

	return ptr;
}
