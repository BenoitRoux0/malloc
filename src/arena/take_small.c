#include <strings.h>

#include "malloc.h"

static void*	worst_or_fit(size_t size);
static void*	sub_arena_worst_or_fit(void* sub_arena, size_t size);

void*	take_small(size_t size, t_chunk_header* hint) {
	t_chunk_header*	chunk = hint;
	t_chunk_header* next_chunk = NULL;

	if (chunk == NULL) {
		chunk = worst_or_fit(size);
	}

	if (chunk == NULL) {
#ifdef DEBUG
		put_str(2, "need to add arena for smalls\n");
#endif
		if (!append_small())
			return NULL;
		chunk = worst_or_fit(size);
	}

	if (chunk == NULL) {
		return NULL;
	}

	if (chunk == hint) {
#ifdef DEBUG
		put_str(2, "expand chunk ");
		put_nbr(2,  chunk->true_size);
		put_str(2, " to ");
		put_nbr(2,  chunk->true_size + get_next_chunk(chunk)->true_size + sizeof (t_chunk_header));
		put_str(2, "\n");
#endif
		chunk->true_size += get_next_chunk(chunk)->true_size + sizeof (t_chunk_header);
	}

#ifdef DEBUG
	put_str(2, "found chunk ");
	put_ptr(2,  chunk->true_size);
	put_str(2, " for ");
	put_nbr(2,  size);
	if (hint)
		put_str(2, " with hint ");
	put_str(2, "\n");
	if (chunk->prec_chunk) {
		put_str(2, "found prec size ");
		put_nbr(2,  chunk->prec_chunk->size);
		put_str(2, "\n");
	}
#endif

	if (size_aligned(size) < chunk->true_size - sizeof(t_chunk_header)) {
		size_t	old_true_size = chunk->true_size;
		chunk->size = size;
		chunk->true_size = size_aligned(size);

#ifdef DEBUG
		put_str(2, "check next chunk\n");
#endif

		next_chunk = get_next_chunk(chunk);
		if (get_main_arena(chunk) == get_main_arena(next_chunk) && (void*) next_chunk < get_border_addr(chunk) - sizeof(t_chunk_header)) {
			next_chunk->owned = false;
			next_chunk->size = old_true_size - sizeof(t_chunk_header) - chunk->true_size;
			next_chunk->true_size = next_chunk->size;
#ifdef DEBUG
			put_str(2, "old_true_size: ");
			put_nbr(2,  old_true_size);
			put_str(2, "\n");
			put_str(2, "current_true_size: ");
			put_nbr(2,  chunk->true_size);
			put_str(2, "\n");
			put_str(2, "next chunk true_size: ");
			put_ptr(2,  next_chunk->true_size);
			put_str(2, "\n");
#endif
			if (next_chunk->true_size > (size_t) g_arenas.small_arena_size) {
#ifdef DEBUG
				put_str(2, "next chunk out of bound\n");
#endif
				return NULL;
			}
			next_chunk->prec_chunk = chunk;
#ifdef DEBUG
			put_str(2, "next chunk prec chunk: ");
			put_ptr(2, (uintptr_t) next_chunk->prec_chunk);
			put_str(2, "\n");
#endif
			if ((void*) get_next_chunk(next_chunk) < get_border_addr(chunk) - sizeof(t_chunk_header)) {
#ifdef DEBUG
				put_str(2, "set get_next_chunk(next_chunk)\n");
#endif
				get_next_chunk(next_chunk)->prec_chunk = next_chunk;
#ifdef DEBUG
				put_str(2, "get_next_chunk(next_chunk) setted with size: ");
				put_nbr(2, next_chunk->true_size);
				put_str(2, "\n");
#endif
			}
		} else {
			chunk->true_size = old_true_size;
		}
	}
	chunk->size = size;
	chunk->owned = true;

	if (!hint)
		++get_main_arena(chunk)->allocated;

#ifdef DEBUG
	put_str(2, "end take small\n\n");
#endif

	return chunk;
}

static void*	worst_or_fit(size_t size) {
	t_chunk_header*	worst = NULL;
	t_chunk_header*	found = NULL;

	for (void* arena_ite = g_arenas.small; arena_ite != NULL; arena_ite = has_arena(arena_ite)->next) {
		found = sub_arena_worst_or_fit(arena_ite, size);

//		if (found) {
//			put_str(1, "found chunk ");
//			put_nbr(1,  found->true_size);
//			put_str(1, " in arena ");
//			put_ptr(1, (uintptr_t)  arena_ite);
//			put_str(1, " for ");
//			put_nbr(1,  size);
//			put_str(1, "\n");
//		}

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

	// put_str(1, "arena:");
	// put_ptr(1, (uintptr_t) sub_arena);
	// put_str(1, "\n");
	for (; chunk_ite < sub_arena + g_arenas.small_arena_size - (sizeof(t_chunk_header) + size_aligned(size)); chunk_ite = get_next_chunk(chunk_ite)) {
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