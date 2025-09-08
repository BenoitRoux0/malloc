#include <strings.h>

#include "malloc.h"

void*	alloc_large(size_t size) {
	t_arena_hdr*	arena_header;
	t_chunk_header*	chunk_header;
	void*			ptr;

	lock_alloc();

#ifdef DEBUG
	put_str(2, "mmap large arena\n");
#endif //DEBUG

	ptr = mmap(NULL, size + sizeof (t_chunk_header) + sizeof (t_arena_hdr), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (ptr == NULL) {
		unlock_alloc();
		return NULL;
	}

	arena_header = ptr;
	chunk_header = ptr + sizeof (t_arena_hdr);
	arena_header->size = size + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
	arena_header->next = g_arenas.large;
	chunk_header->size = size;
	chunk_header->true_size = size;
	chunk_header->owned = true;

	g_arenas.large = arena_header;

#ifdef DEBUG
	if (!get_main_arena(ptr)) {
		put_str(2, "alloc large addr out: ");
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, "\n");
	}
#endif

	unlock_alloc();
	return ptr + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
}
