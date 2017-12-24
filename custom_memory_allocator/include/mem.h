#ifndef CUSTOM_MEMORY_ALLOCATOR_MEM_H
#define CUSTOM_MEMORY_ALLOCATOR_MEM_H

#define __USE_MISC

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)

#pragma pack(push, 1)
typedef struct mem_t {
    struct mem_t* next;
    size_t capacity;
    int is_free;
} MemType;
#pragma pack(pop)

void* _malloc(size_t query);
void _free(void* mem);
void* heap_init(size_t initial_size);

#define DEBUG_FIRST_BYTES 4

void memalloc_debug_struct_info(FILE* f, MemType const* const address);
void memalloc_debug_heap(FILE* f, MemType const* ptr);

#endif //CUSTOM_MEMORY_ALLOCATOR_MEM_H
