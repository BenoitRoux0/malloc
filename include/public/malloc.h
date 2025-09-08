#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>

typedef struct {
	size_t	mmaped_tiny;
	size_t	mmaped_small;
}	t_malloc_data;

/**
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
void*	malloc(size_t size);

/**
 * @brief realloc resizes a memory block allocated by malloc. Takes a pointer and new size.
 * @param ptr Pointer to the malloc'd memory to resize
 * @param size The mew desired size
 * @return returns pointer to resized memory (may be same or different address) or NULL on failure
 */
void*	realloc(void *ptr, size_t size);

/**
 * @brief calloc allocates memory for an array and initializes all bytes to zero.
 * Takes two parameters (number of elements and size of each element)
 * @param nmemb Number of desired members in array
 * @param size Size of the array
 * @return returns a pointer to the zero-initialized memory block or NULL on failure
 */
void*	calloc(size_t nmemb, size_t size);

/**
 * @brief reallocarray resizes array memory like realloc but with overflow protection
 * @param ptr pointer to previously allocated memory block (or NULL for new allocation)
 * @param nmemb number of array elements
 * @param size size in bytes of each element
 * @return Returns resized memory pointer or NULL on failure/overflow
 */
void*	reallocarray(void *ptr, size_t nmemb, size_t size);

void	show_alloc_mem();

# ifdef DEBUG

t_malloc_data	get_malloc_data(void);

# endif // DEBUG

#endif // MALLOC_H
