#include "malloc.h"

void*	alloc_large(size_t size) {
	t_arena_hdr*	arena_header;
	t_chunk_header*	chunk_header;
	void*			ptr;

#ifdef DEBUG
	put_str(1, "mmap arena\n");
#endif //DEBUG

	ptr = mmap(NULL, size + sizeof (t_chunk_header) + sizeof (t_arena_hdr), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	chunk_header = ptr + sizeof (t_arena_hdr);
	arena_header->size = size + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
	arena_header->next = g_arenas.large;
	chunk_header->size = size;
	chunk_header->owned = true;

	g_arenas.large = arena_header;

	return ptr + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
}
