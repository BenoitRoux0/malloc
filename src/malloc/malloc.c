#include "malloc.h"

t_arenas g_arenas = {
	0,
	0,
	NULL,
	0,
	NULL,
	NULL
};

static void*	alloc_tiny(size_t size);
static void*	alloc_small(size_t size);
static void*	alloc_large(size_t size);

void*	malloc(size_t size) {
	if (g_arenas.page_size == 0) {
		g_arenas.page_size = sysconf(_SC_PAGESIZE);
		g_arenas.tiny_arena_size = g_arenas.page_size * TINY_ARENA_SIZE;
		g_arenas.small_arena_size = g_arenas.page_size * SMALL_ARENA_SIZE;
	}

	if (size <= TINY_MAX) {
		return alloc_tiny(size);
	}

	if (size <= SMALL_MAX) {
		return alloc_small(size);
	}

	return alloc_large(size);
}

static void*	alloc_tiny(size_t size) {
	void*	ptr = take_tiny(size);

	return ptr + sizeof (t_chunk_header);
}

static void*	alloc_small(size_t size) {
	void*	ptr = take_small(size);

	return ptr + sizeof (t_chunk_header);
}

static void*	alloc_large(size_t size) {
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
