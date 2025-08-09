#include "malloc.h"

bool	is_out(t_chunk_header* chunk) {
	t_arena_hdr*	arena =  get_main_arena(chunk);

	if (!arena)
		return NULL;

	return get_main_arena((void*) chunk + chunk->true_size - 16) == NULL;
}
