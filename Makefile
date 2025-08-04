ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

BIN_DIR =						./bin/
LIB_DIR =						./lib/

NAME =							$(LIB_DIR)/libft_malloc.so
FULL_NAME =						$(LIB_DIR)/libft_malloc_$(HOSTTYPE).so
NAME_DEBUG =					$(LIB_DIR)/libft_malloc_debug.so
FULL_NAME_DEBUG =				$(LIB_DIR)/libft_malloc_$(HOSTTYPE)_debug.so
FT_TEST_NAME =					$(BIN_DIR)/libft_malloc_test
TEST_NAME =						$(BIN_DIR)/malloc_test
MOCKS_NAME =					$(LIB_DIR)/mocks.a
NAME_MTRACE =					$(BIN_DIR)/mtrace

NAME_BONUS =					$(LIB_DIR)/libft_malloc_bonus.so
FULL_NAME_BONUS = 				$(LIB_DIR)/libft_malloc_$(HOSTTYPE)_bonus.so
NAME_DEBUG_BONUS = 				$(LIB_DIR)/libft_malloc_debug_bonus.so
FULL_NAME_DEBUG_BONUS =			$(LIB_DIR)/libft_malloc_$(HOSTTYPE)_debug_bonus.so
FT_TEST_NAME_BONUS = 			$(BIN_DIR)/libft_malloc_test_bonus
TEST_NAME_BONUS = 				$(BIN_DIR)/malloc_test_bonus
MOCKS_NAME_BONUS =				$(LIB_DIR)/mocks_bonus.a

CC = 							cc

SRC =							src/free/free.c \
								src/free/free_chunk.c \
								src/free/free_tiny.c \
								src/free/free_small.c \
								src/free/free_large.c \
								src/malloc/malloc.c \
								src/malloc/alloc_tiny.c \
								src/malloc/alloc_small.c \
								src/malloc/alloc_large.c \
								src/realloc/realloc.c \
								src/realloc/to_tiny.c \
								src/realloc/to_small.c \
								src/realloc/to_large.c \
								src/calloc/calloc.c \
								src/reallocarray/reallocarray.c \
								src/show_alloc_mem/show_alloc_mem.c \
								src/utils/str.c \
								src/utils/puts.c \
								src/utils/min.c \
								src/utils/get_size_category.c \
								src/utils/ft_memcpy.c \
								src/utils/ft_memmove.c \
								src/utils/lock_alloc.c \
								src/utils/unlock_alloc.c \
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

SRC_DEBUG =						$(SRC) \
								src/get_malloc_data.c

SRC_TEST =						test/src/main.c \
								test/src/run_test.c \
								test/src/run_test_group.c \
								test/src/test_utils.c \
								test/src/tests/tiny_tests.c \
								test/src/tests/small_tests.c \
								test/src/tests/large_tests.c \
								test/src/tests/show_alloc_mem_tests.c \
								test/src/tests/coalescing_tests.c \
								test/src/tests/external_uses_tests.c \
								test/src/tests/realloc/from_tiny.c \
								test/src/tests/realloc/from_small.c \
								test/src/tests/realloc/from_large.c \

SRC_MOCKS = 					test/src/mocks/show_alloc_mem.c \
								test/src/mocks/get_malloc_data.c

SRC_MTRACE =					mtrace/src/main.c \
								mtrace/src/sig_handler.c \

OBJ_DIR =						.objs
OBJ_DEBUG_DIR =					.objs/debug

OBJ =							$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DEBUG =						$(SRC_DEBUG:%.c=$(OBJ_DEBUG_DIR)/%.o)
OBJ_TEST =						$(SRC_TEST:%.c=$(OBJ_DIR)/%.o)
OBJ_MOCKS =						$(SRC_MOCKS:%.c=$(OBJ_DIR)/%.o)
OBJ_MTRACE =					$(SRC_MTRACE:%.c=$(OBJ_DIR)/%.o)

OBJ_BONUS =						$(SRC:%.c=$(OBJ_DIR)/%_bonus.o)
OBJ_DEBUG_BONUS =				$(SRC_DEBUG:%.c=$(OBJ_DEBUG_DIR)/%_bonus.o)
OBJ_TEST_BONUS =				$(SRC_TEST:%.c=$(OBJ_DIR)/%_bonus.o)
OBJ_MOCKS_BONUS =				$(SRC_MOCKS:%.c=$(OBJ_DIR)/%_bonus.o)

CFLAGS =						-Wall -Wextra -Werror -rdynamic -fpic
CFLAGS_DEBUG =					-Wall -Wextra -Werror -rdynamic -fpic  -DDEBUG=1
CFLAGS_TEST =					-Wall -Wextra -Werror -rdynamic  -DDEBUG=1

.PHONY:	all
all:
								$(MAKE) malloc
								$(MAKE) debug
								$(MAKE) bonus
								$(MAKE) debug_bonus
								$(MAKE) test
								$(MAKE) mtrace

.PHONY:	mtrace
mtrace:							$(NAME_MTRACE)

.PHONY:	malloc
malloc:							$(NAME)

.PHONY:	debug
debug:							$(NAME_DEBUG)

.PHONY:	bonus
bonus:							$(NAME_BONUS)

.PHONY:	debug_bonus
debug_bonus:					$(NAME_DEBUG_BONUS)

.PHONY:	test
test:							$(FT_TEST_NAME) $(TEST_NAME)

.PHONY:	test_bonus
test_bonus:						$(FT_TEST_NAME_BONUS) $(TEST_NAME_BONUS)

.PHONY: run_test
run_test:						test
								@mkdir -p .ft_test_out/
								@mkdir -p .test_out/
								@echo "running tests for libft_malloc"
								@TEST_OUT_DIR=./.ft_test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.ft_test_out/faults ./libft_malloc_test
								@echo "running tests for true_malloc"
								@TEST_OUT_DIR=./.test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.test_out/faults ./malloc_test
								@diff .ft_test_out/faults .test_out/faults

$(OBJ_DIR)/mtrace/%.o:			mtrace/%.c	mtrace/include/mtrace.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS) -o $@ -c $< -Imtrace/include  -Iinclude/public

$(OBJ_DIR)/src/%.o:				src/%.c	include/internal/malloc.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS) -o $@ -c $< -Iinclude/internal

$(OBJ_DEBUG_DIR)/src/%.o:		src/%.c	include/internal/malloc.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS_DEBUG) -o $@ -c $< -Iinclude/internal

$(OBJ_DIR)/test/src/%.o:		test/src/%.c include/public/malloc.h test/include/test.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS_TEST) -o $@ -c $< -Iinclude/public -Itest/include

$(OBJ_DIR)/src/%_bonus.o:		src/%.c	include/internal/malloc.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS) -DBONUS=1 -o $@ -c $< -Iinclude/internal

$(OBJ_DEBUG_DIR)/src/%_bonus.o:	src/%.c	include/internal/malloc.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS_DEBUG) -DBONUS=1 -o $@ -c $< -Iinclude/internal

$(OBJ_DIR)/test/src/%_bonus.o:	test/src/%.c include/public/malloc.h test/include/test.h
								@mkdir -p $(shell dirname $@)
								$(CC) $(CFLAGS_TEST) -DBONUS=1 -o $@ -c $< -Iinclude/public -Itest/include

$(NAME_MTRACE):					$(OBJ_MTRACE) | $(BIN_DIR)
								$(CC) $(CFLAGS) -Wl,-rpath=$(PWD)/$(LIB_DIR) -L$(PWD)/$(LIB_DIR) -o $@ $^ -lft_malloc

$(NAME):						$(FULL_NAME) | $(LIB_DIR)
								ln -s $(PWD)/$(FULL_NAME) $(NAME) && echo "link created" || echo "link already exists"

$(NAME_BONUS):					$(FULL_NAME_BONUS) | $(LIB_DIR)
								ln -s $(PWD)/$(FULL_NAME_BONUS) $(NAME_BONUS) && echo "link created" || echo "link already exists"

$(FULL_NAME):					$(OBJ) | $(LIB_DIR)
								$(CC) $(CFLAGS) -shared -o $@ $^

$(FULL_NAME_BONUS):				$(OBJ_BONUS) | $(LIB_DIR)
								$(CC) $(CFLAGS) -shared -o $@ $^

$(NAME_DEBUG):					$(FULL_NAME_DEBUG) | $(LIB_DIR)
								ln -s $(PWD)/$(FULL_NAME_DEBUG) $(NAME_DEBUG) && echo "link created" || echo "link already exists"

$(NAME_DEBUG_BONUS):			$(FULL_NAME_DEBUG_BONUS) | $(LIB_DIR)
								ln -s $(PWD)/$(FULL_NAME_DEBUG_BONUS) $(NAME_DEBUG_BONUS) && echo "link created" || echo "link already exists"

$(FULL_NAME_DEBUG):				$(OBJ_DEBUG) | $(LIB_DIR)
								$(CC) $(CFLAGS_DEBUG) -shared -o $@ $^

$(FULL_NAME_DEBUG_BONUS):		$(OBJ_DEBUG_BONUS) | $(LIB_DIR)
								$(CC) $(CFLAGS_DEBUG) -shared -o $@ $^

$(FT_TEST_NAME):				$(NAME_DEBUG) $(OBJ_TEST) | $(BIN_DIR)
								$(CC) $(CFLAGS_TEST) -L$(PWD)/$(LIB_DIR) -Wl,-rpath=$(PWD)/$(LIB_DIR) -o $@ $(OBJ_TEST) -lft_malloc_debug

$(FT_TEST_NAME_BONUS):			$(NAME_DEBUG_BONUS) $(OBJ_TEST_BONUS) | $(BIN_DIR)
								$(CC) $(CFLAGS_TEST) -L$(PWD)/$(LIB_DIR) -Wl,-rpath=$(PWD)/$(LIB_DIR) -o $@ $(OBJ_TEST_BONUS) -lft_malloc_debug_bonus

$(MOCKS_NAME):					$(OBJ_MOCKS) | $(LIB_DIR)
								ar -rc $@ $(OBJ_MOCKS)

$(MOCKS_NAME_BONUS):			$(OBJ_MOCKS_BONUS) | $(LIB_DIR)
								ar -rc $@ $(OBJ_MOCKS_BONUS)

$(TEST_NAME):					$(OBJ_TEST) $(MOCKS_NAME) | $(BIN_DIR)
								$(CC) $(CFLAGS_TEST) -o $@ $(OBJ_TEST) $(MOCKS_NAME) -ldl

$(TEST_NAME_BONUS):				$(OBJ_TEST_BONUS) $(MOCKS_NAME_BONUS) | $(BIN_DIR)
								$(CC) $(CFLAGS_TEST) -o $@ $(OBJ_TEST_BONUS) $(MOCKS_NAME_BONUS) -ldl

$(BIN_DIR):
								mkdir -p $@

$(LIB_DIR):
								mkdir -p $@

.PHONY: clean
clean:
								$(RM) -r $(OBJ_DIR)

.PHONY: fclean
fclean:							clean
								$(RM) -r doc
								$(RM) -r $(BIN_DIR)
								$(RM) -r $(LIB_DIR)

.PHONY: doc
doc:
								doxygen

.PHONY: re
re:								fclean
								$(MAKE) all
