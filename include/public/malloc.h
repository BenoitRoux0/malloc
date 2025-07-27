#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>

typedef struct {
	size_t	mmaped_tiny;
	size_t	mmaped_small;
}	t_malloc_data;

/**
 * @fn void	free(void *ptr)
 * @brief Function to free an allocated memory
 *
 * @param ptr pointer to be free
 */
void	free(void *ptr);

/**
 * @brief Memory Allocator that allocate a block of given size
 * @param size The size of the block allocated
 * @return A pointer to the Allocated memory. NULL in case of error
 */
void	*malloc(size_t size);

/**
 * @brief
 * @param ptr Pointer to the malloc'd memory to resize
 * @param size The mew desired size
 * @return the new pointer
 */
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem();

# ifdef DEBUG

t_malloc_data	get_malloc_data(void);

# endif // DEBUG

#endif // MALLOC_H
