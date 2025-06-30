#include "malloc.h"

static void*	find_chunk(void* arena_ptr);

void*	take_tiny(size_t size) {
	t_chunk_header*	ptr = NULL;

	for (t_arena_hdr* arena_ite = g_arenas.tiny; arena_ite != NULL; arena_ite = arena_ite->next) {
		ptr = find_chunk(arena_ite);

		if (ptr != NULL) {
			ptr->size = size;
			ptr->owned = true;
			++arena_ite->allocated;
			// put_str(1, "taken: ");
			// put_hexa(1, arena_ite->allocated);
			// put_str(1, "\n");
			return ptr;
		}
	}

	t_arena_hdr*	new_arena = append_tiny();

	ptr = find_chunk(new_arena);

	if (ptr == NULL)
		return NULL;

	ptr->size = size;
	ptr->owned = true;
	++new_arena->allocated;

	return ptr;
}

static void*	find_chunk(void* arena_ptr) {
	for (void* sub_arena = arena_ptr; sub_arena < (arena_ptr + (g_arenas.tiny_arena_size)); sub_arena += g_arenas.page_size) {
		for (void* chunk_ite = sub_arena + sizeof(t_arena_hdr); chunk_ite < (sub_arena + g_arenas.page_size); chunk_ite += (sizeof(t_chunk_header) + TINY_MAX)) {
			if (has_chunk(chunk_ite)->owned == false) {
				return chunk_ite;
			}
		}
	}
	return NULL;
}
