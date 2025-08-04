#include "malloc.h"

/**
 * @brief Free the allocated memory
 * @param ptr The pointer to memory to be freed
 */
void	free(void *ptr) {
#ifdef DEBUG
	put_str(2, "free: ");
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, "\n");
#endif

	if (ptr == NULL)
		return;

	t_chunk_header*	chunk_header = ptr - sizeof(t_chunk_header);

	if (!chunk_header->owned)
		return;

	free_chunk(chunk_header);

#ifdef DEBUG
	put_ptr(2, (uintptr_t) ptr);
	put_str(2, " freed");
	put_str(2, "\n");
#endif
}


