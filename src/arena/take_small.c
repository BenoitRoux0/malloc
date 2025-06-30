#include "malloc.h"

static void*			worst_or_fit(size_t size);
static void*	sub_arena_worst_or_fit(void* sub_arena, size_t size);

void*	take_small(size_t size) {
	t_chunk_header*	chunk = worst_or_fit(size);

	if (chunk == NULL)
		append_small();

	chunk = worst_or_fit(size);
	if (chunk == NULL)
		return NULL;

	if (chunk->size - size > 16) {
		size_t	old_size = chunk->size;
		chunk->size = size;

		t_chunk_header* next_chunk = chunk + get_chunk_size(chunk);
		if ((void*) next_chunk < get_next_page(chunk)) {
			next_chunk->owned = false;
			next_chunk->size = old_size - sizeof(t_chunk_header) - get_chunk_size(chunk);
		}
	}
	chunk->size = size;
	chunk->owned = true;

	++get_main_arena(chunk)->allocated;

	return chunk;
}

static void*	worst_or_fit(size_t size) {
	t_chunk_header*	worst = NULL;
	t_chunk_header*	found = NULL;

	for (void* arena_ite = g_arenas.small; arena_ite != NULL; arena_ite = has_arena(arena_ite)->next) {
		for (void* sub_arena = arena_ite; sub_arena < arena_ite + (g_arenas.tiny_arena_size); sub_arena += g_arenas.page_size) {
			found = sub_arena_worst_or_fit(sub_arena, size);
			if (!found || found->size == 0 || found->size < size) {
				continue;
			}

			if (found->size == size || found->size == g_arenas.page_size - sizeof (t_arena_hdr)) {
				return found;
			}

			if (worst == NULL || found->size < worst->size) {
				worst = found;
			}
		}
	}

	return worst;
}

static void*	sub_arena_worst_or_fit(void* sub_arena, size_t size) {
	t_chunk_header*	worst = NULL;
	void* chunk_ite = sub_arena + sizeof(t_arena_hdr);

	// if (!((t_arena_hdr*) sub_arena)->initialized) {
	// 	((t_arena_hdr*) sub_arena)->initialized = true;
	// 	has_chunk(chunk_ite)->size = sysconf(_SC_PAGESIZE) - sizeof (t_arena_hdr);
	// }

	for (; chunk_ite < sub_arena + g_arenas.page_size; chunk_ite = get_next_chunk(chunk_ite)) {
		if (has_chunk(chunk_ite)->owned) {
			continue;
		}

		if (!worst || worst->size < has_chunk(chunk_ite)->size) {
			worst = chunk_ite;
		}

		if (has_chunk(chunk_ite)->size == size || has_chunk(chunk_ite)->size == g_arenas.page_size - sizeof (t_arena_hdr)) {
			return chunk_ite;
		}
	}

	return worst;
}