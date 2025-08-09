#include <strings.h>

#include "malloc.h"

static bool	can_expand_on_next(t_chunk_header* chunk_header, size_t size);

void*	to_small(t_chunk_header* chunk_header, size_t size) {
	if (get_size_category(chunk_header->size) == SMALL && size <= chunk_header->size) {
#ifdef DEBUG
		put_str(2, "reduce small size\n");
#endif
		chunk_header->size = size;
		return (void*) chunk_header + sizeof(t_chunk_header);
	}

	if (get_size_category(chunk_header->size) == TINY || get_size_category(chunk_header->size) == LARGE || !can_expand_on_next(chunk_header, size)) {
#ifdef DEBUG
		put_str(2, "realloc need new small\n");
#endif
		uint8_t* new_ptr = alloc_small(size, NULL);
		t_chunk_header* new_chunk = (void*) new_ptr - sizeof(t_chunk_header);

		if (!new_ptr) {
#ifdef DEBUG
			put_str(2, "new ptr failed\n");
#endif
			return NULL;
		}

		uint8_t*	old_ptr = (void*) chunk_header + sizeof(t_chunk_header);
//		bzero(new_ptr, new_chunk->true_size);
		size_t		copy_size = min(chunk_header->true_size, new_chunk->true_size);

#ifdef DEBUG
		put_str(2, "new ptr alloc'd\n");
#endif

		if (get_size_category(chunk_header->size) == TINY)
			copy_size = TINY_MAX;

		ft_memmove(new_ptr, old_ptr, copy_size);

		free_chunk(chunk_header);
		return new_ptr;
	}

#ifdef DEBUG
	put_str(2, "realloc expand small\n");
#endif
	return alloc_small(size, chunk_header);
}

static bool	can_expand_on_next(t_chunk_header* chunk_header, size_t size) {
	t_chunk_header *next_chunk =  get_next_chunk(chunk_header);

	if (next_chunk->owned)
		return false;

	if (next_chunk->true_size + chunk_header->true_size + sizeof(t_chunk_header) > size_aligned(size)) {
//		put_str(2, "can expand chunk ");
//		put_nbr(2,  chunk_header->true_size);
//		put_str(2, " to ");
//		put_nbr(2,  chunk_header->true_size + next_chunk->true_size + sizeof (t_chunk_header));
//		put_str(2, "\n");
		return true;
	}

	return false;
}
