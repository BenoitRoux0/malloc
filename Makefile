ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
FULL_NAME = libft_malloc_$(HOSTTYPE).so
NAME_DEBUG = libft_malloc_debug.so
FULL_NAME_DEBUG = libft_malloc_$(HOSTTYPE)_debug.so
FT_TEST_NAME = libft_malloc_test
TEST_NAME = malloc_test
MOCKS_NAME = mocks.a

CC = gcc

SRC =	src/free/free.c \
		src/malloc/malloc.c \
		src/malloc/alloc_tiny.c \
		src/malloc/alloc_small.c \
		src/malloc/alloc_large.c \
		src/realloc/realloc.c \
		src/show_alloc_mem/show_alloc_mem.c \
		src/utils/str.c \
		src/utils/puts.c \
		src/utils/min.c \
		src/arena/append_tiny.c \
		src/arena/append_small.c \
		src/arena/take_tiny.c \
		src/arena/take_small.c \
		src/arena/update_after_free.c \
		src/arena/get_main.c \
		src/chunk/get_chunk_size.c \
		src/chunk/get_next_page.c \
		src/chunk/get_main_arena.c \
		src/chunk/get_border_addr.c

SRC_DEBUG =	$(SRC) \
			src/get_malloc_data.c

SRC_TEST =	test/src/main.c \
			test/src/run_test.c \
			test/src/run_test_group.c \
			test/src/test_utils.c \
			test/src/tests/tiny_tests.c \
			test/src/tests/small_tests.c \
			test/src/tests/large_tests.c \
			test/src/tests/show_alloc_mem_tests.c \
			test/src/tests/coalescing_tests.c \
			test/src/tests/realloc_tests.c \

SRC_MOCKS = test/src/mocks/show_alloc_mem.c \
			test/src/mocks/get_malloc_data.c

OBJ_DIR = .objs
OBJ_DEBUG_DIR = .objs/debug

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DEBUG =	$(SRC_DEBUG:%.c=$(OBJ_DEBUG_DIR)/%.o)
OBJ_TEST =	$(SRC_TEST:%.c=$(OBJ_DIR)/%.o)
OBJ_MOCKS =	$(SRC_MOCKS:%.c=$(OBJ_DIR)/%.o)

CFLAGS =		-Wall -Wextra -Werror -fpic
CFLAGS_DEBUG =	-Wall -Wextra -Werror -fpic -g3 -DDEBUG=1
CFLAGS_TEST =	-Wall -Wextra -Werror -g3 -DDEBUG=1

all:	test

test:	$(FT_TEST_NAME) $(TEST_NAME)

run_test:	test
			@mkdir -p .ft_test_out/
			@mkdir -p .test_out/
			@echo "running tests for libft_malloc"
			@TEST_OUT_DIR=./.ft_test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.ft_test_out/faults ./libft_malloc_test
			@echo "running tests for true_malloc"
			@TEST_OUT_DIR=./.test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.test_out/faults ./malloc_test
			@diff .ft_test_out/faults .test_out/faults

$(OBJ_DIR)/src/%.o:		src/%.c	include/internal/malloc.h
						@mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS) -o $@ -c $< -Iinclude/internal

$(OBJ_DEBUG_DIR)/src/%.o:		src/%.c	include/internal/malloc.h
						@mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS_DEBUG) -o $@ -c $< -Iinclude/internal

$(OBJ_DIR)/test/src/%.o:	test/src/%.c include/public/malloc.h test/include/test.h
							@mkdir -p $(shell dirname $@)
							$(CC) $(CFLAGS_TEST) -o $@ -c $< -Iinclude/public -Itest/include

$(NAME):				$(FULL_NAME)
						ln -s $(FULL_NAME) $(NAME) && echo "link created" || echo "link already exists"

$(FULL_NAME):			$(OBJ)
						$(CC) -shared -o $@ $^

$(NAME_DEBUG):			$(FULL_NAME_DEBUG)
						ln -s $(FULL_NAME_DEBUG) $(NAME_DEBUG) && echo "link created" || echo "link already exists"

$(FULL_NAME_DEBUG):		$(OBJ_DEBUG)
						$(CC) -shared -o $@ $^

$(FT_TEST_NAME):		$(NAME_DEBUG) $(OBJ_TEST)
						$(CC) -L. -Wl,-rpath=. -o $@ $(OBJ_TEST) -lft_malloc_debug

$(MOCKS_NAME):			$(OBJ_MOCKS)
						ar -rc $@ $(OBJ_MOCKS)

$(TEST_NAME):			$(OBJ_TEST) $(MOCKS_NAME)
						$(CC) -o $@ $(OBJ_TEST) $(MOCKS_NAME)

clean:
						$(RM) -r $(OBJ_DIR)

fclean:					clean
						$(RM) $(NAME)
						$(RM) $(FULL_NAME)
						$(RM) $(NAME_DEBUG)
						$(RM) $(FULL_NAME_DEBUG)
						$(RM) $(TEST_NAME)
						$(RM) $(FT_TEST_NAME)
						$(RM) $(MOCKS_NAME)
						$(RM) -r doc

doc:
						doxygen

re:						fclean
						$(MAKE) all
