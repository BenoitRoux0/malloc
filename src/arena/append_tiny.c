#include <string.h>

#include "malloc.h"

void*	append_tiny(void) {
	t_arena_hdr*	arena_header;
	void*			ptr;

#ifdef DEBUG
	put_str(2, "mmap tiny arena\n");
#endif //DEBUG
	ptr = mmap(NULL, g_arenas.tiny_arena_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	arena_header->allocated = 0;
	arena_header->size = g_arenas.tiny_arena_size;
	arena_header->next = g_arenas.tiny;

	g_arenas.tiny = arena_header;

	return ptr;
}
