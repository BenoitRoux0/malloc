#include "malloc.h"

void*	get_next_page(void* chunk) {
	return chunk - ((uintptr_t) chunk % g_arenas.page_size) + g_arenas.page_size;
}
