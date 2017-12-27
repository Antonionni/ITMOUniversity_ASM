#ifndef CUSTOM_MEMORY_ALLOCATOR_MEM_H
#define CUSTOM_MEMORY_ALLOCATOR_MEM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)
#define DEBUG_FIRST_BYTES 4
#define MINIMAL_BLOCK_SIZE 4

#pragma pack(push, 1)
typedef struct mem_t {
    struct mem_t* next;
    size_t capacity;
    int is_free;
} MemType;
#pragma pack(pop)

void* _calloc(const size_t n, const size_t query);
void set_zero(void *ptr, size_t size);
void* _malloc(size_t query);
void _free(void* memory);
void* heap_init(size_t initial_size);
void *allocate(MemType *heap_pointer, const size_t query);

size_t real_page_address(void *address);


void memalloc_debug_struct_info(FILE* f, MemType const* const address);
void memalloc_debug_heap(FILE* f, MemType const* ptr);

#endif //CUSTOM_MEMORY_ALLOCATOR_MEM_H
