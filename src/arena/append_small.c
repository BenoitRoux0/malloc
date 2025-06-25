#include <string.h>

#include "malloc.h"

void*	append_small(void) {
	t_arena_hdr*	arena_header;
	void*			ptr;

	put_str(1, "mmap arena\n");
	ptr = mmap(NULL, sysconf(_SC_PAGESIZE) * SMALL_ARENA_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	arena_header->allocated = 0;
	arena_header->size = sysconf(_SC_PAGESIZE) * SMALL_ARENA_SIZE;
	arena_header->next = g_arenas.small;

	g_arenas.small = arena_header;

	memset(ptr + sizeof(t_arena_hdr), 0, sysconf(_SC_PAGESIZE) * SMALL_ARENA_SIZE - sizeof(t_arena_hdr));

	for (void*	arena_ptr = arena_header; arena_ptr < (ptr + SMALL_ARENA_SIZE * sysconf(_SC_PAGESIZE)); arena_ptr += sysconf(_SC_PAGESIZE)) {
		void*	chunk_header = arena_ptr + sizeof (t_arena_hdr);

		((t_chunk_header*) chunk_header)->size = sysconf(_SC_PAGESIZE) - sizeof (t_arena_hdr);
	}

	return ptr;
}