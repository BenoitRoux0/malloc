#!/bin/bash

declare -a tests=(
"test_instant_free_tiny"
"test_free_after_tiny"
"test_instant_free_small"
"test_free_after_small"
"test_large"
"test_very_large"
"show_alloc_mem_tests"
)

for i in "${tests[@]}"; do
  echo "run $i:"

  mkdir -p .test_out/
  mkdir -p .ft_test_out/

  TEST_OUT_DIR=./.ft_test_out/ /usr/bin/time --format='ft major: %F\nft minor: %R' ./libft_malloc_test "$i" > /dev/null
  TEST_OUT_DIR=./.test_out/ /usr/bin/time --format='major: %F\nminor: %R' ./malloc_test "$i" > /dev/null
  echo "" >&2
done
