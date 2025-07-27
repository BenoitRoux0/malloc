#include "malloc.h"

static void*			worst_or_fit(size_t size);
static void*	sub_arena_worst_or_fit(void* sub_arena, size_t size);

void*	take_small(size_t size) {
	t_chunk_header*	chunk = worst_or_fit(size);
	t_chunk_header* next_chunk = NULL;

	if (chunk == NULL) {
		append_small();
		chunk = worst_or_fit(size);
	}

	if (chunk == NULL) {
		return NULL;
	}

	if (chunk->size - size > sizeof(t_chunk_header)) {
		size_t	old_true_size = chunk->true_size;
		chunk->size = size;
		chunk->true_size = get_chunk_size(chunk);

		next_chunk = get_next_chunk(chunk);
		if ((void*) next_chunk < get_border_addr(chunk)) {
			next_chunk->owned = false;
			next_chunk->size = size_aligned(old_true_size) - sizeof(t_chunk_header) - chunk->true_size;
			next_chunk->true_size = next_chunk->size;
			next_chunk->prec_chunk = chunk;
			if ((void*) get_next_chunk(next_chunk) < get_border_addr(chunk)) {
				get_next_chunk(next_chunk)->prec_chunk = next_chunk;
			}
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
			found = sub_arena_worst_or_fit(arena_ite, size);
			if (!found ||
				found->size == 0 ||
				found->true_size < size) {
				continue;
			}

			if (found->true_size == size_aligned(size) ||
				found->true_size == g_arenas.small_arena_size - sizeof (t_arena_hdr)) {
				return found;
			}

			if (worst == NULL || found->true_size < worst->true_size) {
				worst = found;
			}
	}

	return worst;
}

static void*	sub_arena_worst_or_fit(void* sub_arena, size_t size) {
	t_chunk_header*	worst = NULL;
	void* chunk_ite = sub_arena + sizeof(t_arena_hdr);

	for (; chunk_ite < sub_arena + g_arenas.small_arena_size; chunk_ite = get_next_chunk(chunk_ite)) {
		if (has_chunk(chunk_ite)->owned ||
			has_chunk(chunk_ite)->true_size < size) {
			continue;
		}

		if (has_chunk(chunk_ite)->true_size == size_aligned(size) ||
			has_chunk(chunk_ite)->true_size == g_arenas.small_arena_size - sizeof (t_arena_hdr)) {
			return chunk_ite;
		}

		if (!worst || worst->true_size < has_chunk(chunk_ite)->true_size) {
			worst = chunk_ite;
		}
	}

	return worst;
}