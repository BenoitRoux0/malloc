#include <string.h>

#include "malloc.h"

void*	append_small(void) {
	t_arena_hdr*	arena_header;
	void*			ptr;

#ifdef DEBUG
	put_str(2, "small arena\n");
#endif //DEBUG
	ptr = mmap(NULL, g_arenas.small_arena_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	arena_header->size = g_arenas.small_arena_size;
	arena_header->next = g_arenas.small;

	g_arenas.small = arena_header;

	void *chunk_header = (void *) arena_header + sizeof(t_arena_hdr);

	has_chunk(chunk_header)->true_size = g_arenas.small_arena_size - sizeof (t_arena_hdr);
	has_chunk(chunk_header)->size = g_arenas.small_arena_size - sizeof (t_arena_hdr);

	// for (void*	arena_ptr = arena_header; arena_ptr < ptr + g_arenas.tiny_arena_size; arena_ptr += g_arenas.page_size) {
	// 	chunk_header = arena_ptr + sizeof(t_arena_hdr);
	//
	// 	has_chunk(chunk_header)->size = g_arenas.page_size - sizeof (t_arena_hdr);
	// }

	return ptr;
}