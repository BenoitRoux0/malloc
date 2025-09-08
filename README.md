# libft_malloc

A custom implementation of the malloc family of functions in C, featuring a multi-arena memory allocator with size-based categorization and thread safety.

## 📖 Overview

This project implements a complete memory allocation library that replaces the standard C library's malloc functions. The allocator is designed with performance and efficiency in mind, using different allocation strategies based on allocation size categories.

## ✨ Features

- **Multi-size allocation strategy**: Different algorithms for tiny, small, and large allocations
- **Thread-safe operations**: Mutex-based locking for concurrent access (bonus feature)
- **Memory debugging support**: Debug builds with additional tracking capabilities
- **Complete malloc family**: Implementation of `malloc`, `free`, `realloc`, `calloc`, and `reallocarray`
- **Memory visualization**: `show_alloc_mem()` function for debugging memory usage
- **Comprehensive testing suite**: Extensive tests for all allocation scenarios

## 🏗️ Architecture

### Size Categories

The allocator categorizes memory requests into three types:

- **Tiny allocations**: Small memory blocks (optimized for frequent small allocations)
- **Small allocations**: Medium-sized memory blocks 
- **Large allocations**: Large memory blocks (handled separately with mmap)

### Key Components

```
src/
├── malloc/          # Memory allocation
├── free/            # Memory deallocation
├── realloc/         # Memory reallocation
├── calloc/          # Zero-initialized allocation
├── reallocarray/    # Array reallocation with overflow protection
├── arena/           # Arena management for tiny/small allocations
├── chunk/           # Chunk manipulation utilities
├── utils/           # Helper functions and utilities
└── show_alloc_mem/  # Memory visualization tools
```

## 🚀 Getting Started

### Prerequisites

- GCC or Clang compiler
- Make
- Linux/Unix environment
- POSIX-compliant system

### Building

Build the library:
```bash
make
```

Build with debug information:
```bash
make debug
```

Build with bonus features:
```bash
make bonus
```

Build debug version with bonus features:
```bash
make debug_bonus
```

Clean build artifacts:
```bash
make clean
```

Remove all generated files:
```bash
make fclean
```

### Installation

The build process creates several library variants in the `lib/` directory:

- `libft_malloc.so` - Standard version
- `libft_malloc_debug.so` - Debug version with additional tracking
- `libft_malloc_bonus.so` - Bonus features version
- `libft_malloc_debug_bonus.so` - Debug version with bonus features
- Platform-specific versions (e.g., `libft_malloc_x86_64_Linux.so`)

## 🧪 Testing

### Running Tests

Build the test suite:
```bash
make test
```

Run the test suite:
```bash
make run_test
```

Run specific test groups:
```bash
./bin/libft_malloc_test [test_name]
```

### Test Categories

The test suite covers:
- Tiny allocation tests
- Small allocation tests  
- Large allocation tests
- Realloc operations from different size categories
- Calloc zero-initialization
- Reallocarray overflow protection
- Memory alignment and boundary conditions

## 📚 API Reference

### Core Functions

```c
void* malloc(size_t size);
```
Allocates a block of memory of the specified size.

```c
void free(void *ptr);
```
Frees previously allocated memory.

```c
void* realloc(void *ptr, size_t size);
```
Resizes a previously allocated memory block.

```c
void* calloc(size_t nmemb, size_t size);
```
Allocates memory for an array and initializes it to zero.

```c
void* reallocarray(void *ptr, size_t nmemb, size_t size);
```
Resizes array memory with overflow protection.

### Debug Functions

```c
void show_alloc_mem(void);
```
Displays current memory allocation status (available in all builds).

```c
t_malloc_data get_malloc_data(void);
```
Returns allocation statistics (DEBUG builds only).

## 🔧 Usage Examples

### Basic Usage

```c
#include <malloc.h>

int main() {
    // Allocate memory
    char *buffer = malloc(1024);
    if (!buffer) {
        return 1; // Allocation failed
    }
    
    // Use the memory
    strcpy(buffer, "Hello, World!");
    
    // Resize if needed
    buffer = realloc(buffer, 2048);
    
    // Free when done
    free(buffer);
    
    return 0;
}
```

### Using with LD_PRELOAD

Replace system malloc:
```bash
export LD_PRELOAD="./lib/libft_malloc.so"
./your_program
```

### Memory Debugging

```c
#include <malloc.h>

int main() {
    malloc(100);
    malloc(1000);
    malloc(10000);
    
    // Display memory layout
    show_alloc_mem();
    
    return 0;
}
```

## 🧰 Development

### Project Structure

```
├── include/
│   ├── internal/    # Internal header files
│   └── public/      # Public API headers
├── src/             # Source code organized by functionality
├── test/            # Comprehensive test suite
├── lib/             # Generated libraries
├── bin/             # Generated binaries
└── doc/             # Generated documentation
```

### Code Style

The project follows a consistent coding style enforced by `.clang-format`. Format code with:
```bash
clang-format -i src/**/*.c include/**/*.h
```

### Documentation

Generate API documentation with Doxygen:
```bash
doxygen Doxyfile
```

Documentation will be available in `doc/html/index.html`.

## ⚡ Performance Considerations

- **Size-based optimization**: Different allocation strategies minimize fragmentation
- **Arena allocation**: Reduces system call overhead for small allocations
- **Thread safety**: Minimal locking overhead while ensuring correctness
- **Memory alignment**: Proper alignment for optimal CPU cache performance

## 🐛 Debugging

### Debug Build

Use the debug version for development:
```bash
make debug
export LD_PRELOAD="./lib/libft_malloc_debug.so"
```

### Memory Visualization

The `show_alloc_mem()` function provides insights into:
- Current allocations by size category
- Memory fragmentation
- Arena utilization
- Large allocation tracking

### Common Issues

- **Segmentation faults**: Often caused by double-free or use-after-free
- **Memory leaks**: Use `show_alloc_mem()` to track unfreed allocations
- **Performance issues**: Check allocation patterns and consider size category optimization

## 📄 License

This project is part of the 42 School curriculum. Please respect academic integrity guidelines when using this code.
