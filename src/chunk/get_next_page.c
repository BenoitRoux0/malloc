#include "malloc.h"

void*	get_next_page(void* chunk) {
	return chunk - ((uintptr_t) chunk % sysconf(_SC_PAGESIZE)) + sysconf(_SC_PAGESIZE);
}
