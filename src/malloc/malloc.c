#include "malloc.h"

t_arenas g_arenas = {NULL, NULL, NULL};

static void*	alloc_tiny(size_t size);
static void*	alloc_small(size_t size);
static void*	alloc_large(size_t size);

void*	malloc(size_t size) {
	// put_str(1, "call malloc\n");
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
	t_arena_hdr*	tmp = g_arenas.large;

	put_str(1, "mmap arena\n");
	ptr = mmap(NULL, size + sizeof (t_chunk_header) + sizeof (t_arena_hdr), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	arena_header = ptr;
	arena_header->is_main = true;
	chunk_header = ptr + sizeof (t_arena_hdr);
	arena_header->size = size + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
	arena_header->next = NULL;
	chunk_header->size = size;
	chunk_header->owned = true;

	if (g_arenas.large == NULL) {
		g_arenas.large = arena_header;
	} else {
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = ptr;
	}

	return ptr + sizeof (t_chunk_header) + sizeof (t_arena_hdr);
}
