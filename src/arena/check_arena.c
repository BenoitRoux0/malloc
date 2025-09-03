#include "malloc.h"

bool	check_arena(void* to_check) {
	void* chunk_ite = to_check + sizeof(t_arena_hdr);
	size_t	count = 0;

	for (; (void*) get_next_chunk(chunk_ite) < to_check + g_arenas.small_arena_size - sizeof(t_chunk_header); chunk_ite = get_next_chunk(chunk_ite)) {
		if (chunk_ite != get_next_chunk(chunk_ite)->prec_chunk) {
			put_str(2, "check_arena: ");
			put_nbr(2, count);
			put_str(2, "\n");

			return false;
		}

		++count;
	}

	return true;
}
