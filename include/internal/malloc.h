#ifndef MALLOC_H
# define MALLOC_H

# include <stdbool.h>
# include <sys/mman.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>

# ifdef BONUS
#  include <pthread.h>
# endif


# define TINY_MAX 16
# define TINY_ARENA_SIZE 16

# define SMALL_MAX 1024
# define SMALL_ARENA_SIZE 128

# define has_chunk(ptr) ((t_chunk_header*) (ptr))
# define has_arena(ptr) ((t_arena_hdr*) (ptr))

#define get_next_chunk(chunk) has_chunk((((void*) chunk) + (sizeof(t_chunk_header) + has_chunk(chunk)->true_size)))

#define size_aligned(size) ((size) % 16 == 0 ? (size + 32) : ((size) + (16 - ((size) % 16) + 32)))

typedef struct {
	size_t	mmaped_tiny;
	size_t	mmaped_small;
}	t_malloc_data;

typedef enum e_size_category {
	TINY,
	SMALL,
	LARGE
}	t_size_category;

typedef struct s_arena_hdr {
	bool				is_main;
	uint8_t				_[6];
	size_t				size;
	size_t				allocated;
	struct s_arena_hdr*	next;
}	t_arena_hdr;

typedef struct s_arenas {
	long int		page_size;
	long int		tiny_arena_size;
	t_arena_hdr*	tiny;
	long int		small_arena_size;
	t_arena_hdr*	small;
	t_arena_hdr*	large;
}	t_arenas;

typedef struct s_chunk_header {
	struct s_chunk_header*	prec_chunk;
	bool					owned;
	size_t					true_size;
	size_t					size;
}	t_chunk_header;

extern	t_arenas g_arenas;

#ifdef BONUS
extern	pthread_mutex_t g_alloc_mutex;
#endif

// arenas
void*	take_tiny(size_t size);
void*	append_tiny(void);

void	update_after_free_small(void);
void*	take_small(size_t size, t_chunk_header* hint);
void*	append_small(void);

void	update_after_free_tiny(void);
void	remove_arena(t_arena_hdr** target, t_arena_hdr* to_remove);
void*	get_main(void* arena);

// chunks
size_t			get_chunk_size(const void* chunk);
void*			get_next_page(void* chunk);
t_arena_hdr*	get_main_arena(void* chunk);
void*			get_border_addr(t_chunk_header* chunk);

// utils
size_t			ft_strlen(const char* s);
ssize_t			put_str(int fd, char* s);
void			put_ptr(int fd, uintptr_t val);
ssize_t			put_hexa(int fd, size_t val);
ssize_t			put_nbr(int fd, size_t val);
size_t			min(size_t x, size_t y);
t_size_category	get_size_category(size_t size);
void*			ft_memcpy(void *dst, const void *src, size_t n);
void*			ft_memmove(void* dst, const void* src, size_t len);
void			lock_alloc(void);
void			unlock_alloc(void);

void	free(void *ptr);
void	free_chunk(t_chunk_header* chunk_ptr);
void	free_tiny(void* chunk_ptr);
void	free_small(void* chunk_ptr);
void	free_large(void* chunk_ptr);

void*	malloc(size_t size);
void*	alloc_tiny(size_t size);
void*	alloc_small(size_t size, t_chunk_header* hint);
void*	alloc_large(size_t size);

void*	realloc(void *ptr, size_t size);
void*	to_tiny(t_chunk_header* chunk_header, size_t size);
void*	to_small(t_chunk_header* chunk_header, size_t size);
void*	to_large(t_chunk_header* chunk_header, size_t size);

void*	calloc(size_t nmemb, size_t size);

void*	reallocarray(void *ptr, size_t nmemb, size_t size);

#endif // MALLOC_H
