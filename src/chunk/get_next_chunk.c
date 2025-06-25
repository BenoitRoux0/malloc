#include "malloc.h"

void*	get_next_chunk(void* chunk) {
	return chunk + (sizeof(t_chunk_header) + get_chunk_size(chunk));
}