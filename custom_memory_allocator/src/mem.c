#include "mem.h"
#include <stdbool.h>

static MemType *heap;

void* _malloc(size_t query) {
    if (heap != HEAP_START || heap == NULL) {
        heap = heap_init(query);
    }
    if (heap == NULL || heap == MAP_FAILED) {
        fprintf(stderr, "Can`t malloc. heap does not initialize");
        return NULL;
    }

    if (query < MINIMAL_BLOCK_SIZE) {
        query = MINIMAL_BLOCK_SIZE;
    }

    //find suitable block
    MemType *find_heap = NULL;
    MemType *last_block = NULL;

    for (MemType *current = heap; current != NULL; current = current->next) {
        if (current->is_free) {
            if (query > current->capacity - sizeof(MemType) - MINIMAL_BLOCK_SIZE) {
                //try merger two blocks
                if (current->next != NULL && current->next->is_free) {
                    current->capacity += current->next->capacity + sizeof(MemType);
                    current->next = current->next->next;
                }
            }
            if (query <= current->capacity - sizeof(MemType) - MINIMAL_BLOCK_SIZE) {
                find_heap = current;
                current->is_free = false;
                break;
            }
        }
        last_block = current;
    }
    if (find_heap == NULL) {
        // we can`t find suitable block; try allocate
        find_heap = allocate(last_block, query);
        if (find_heap == NULL) {
            return NULL;
        }
    }
    MemType *end_block = ((size_t )find_heap + sizeof(MemType) + query);
    find_heap->is_free = false;
    find_heap->capacity = query;

    return (void *)((size_t)find_heap + sizeof(MemType));
}

void *allocate(MemType *heap_pointer, const size_t query) {
    void *address = real_page_address((void *)((size_t)heap_pointer + sizeof(MemType) + heap_pointer->capacity));
    size_t size = (size_t)real_page_address((void*)(query + sizeof(MemType)));

    MemType *new_page = (MemType *)mmap(address, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    if (new_page == MAP_FAILED) {
        new_page = (MemType*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (new_page == MAP_FAILED) {
            fprintf(stderr, "Can`t allocate memory; sorry brother:(\n");
        }
    }
    heap_pointer->next = new_page;
    new_page->next = NULL;
    new_page->capacity = size - sizeof(MemType);
    new_page->is_free = true;
    return new_page;
}
void* heap_init(size_t initial_size) {
    if (initial_size <= 0) {
        fprintf(stderr, "Initial size is less or equal zero, please write normal size.\n");
        return NULL;
    }
    size_t size = real_page_address((void *)(initial_size + sizeof(MemType)));
    heap = (MemType*)mmap(HEAP_START, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (heap == NULL) {
        fprintf(stderr, "Can`t mmap memory\n");
        return NULL;
    }
    heap->next = NULL;
    heap->capacity = size - sizeof(MemType);
    heap->is_free = true;
}

size_t real_page_address(void *address) {
    int size = sysconf(_SC_PAGESIZE);
    size_t addr = (size_t)address;
    addr = addr - addr % size + size;
    return (void*)addr;
}
void _free(void* memory) {
    MemType *curent_ptr = (MemType*)(memory - sizeof(MemType));
    curent_ptr->is_free = true;
    if (curent_ptr->next != NULL && curent_ptr->next->is_free) {
        curent_ptr->capacity += curent_ptr->next->capacity + sizeof(MemType);
        curent_ptr->next = curent_ptr->next->next;
    }
    return;
}
void* _calloc(const size_t n, const size_t query) {
    size_t summ_size = n * query;
    void *result_ptr = _malloc(summ_size);
    if (result_ptr == NULL) {
        fprintf(stderr, "Ca`t calloc memory\n");
        return NULL;
    }
    set_zero(result_ptr, summ_size);
    return result_ptr;
}
void set_zero(void *ptr, size_t size) {
    char *convert_ptr = (char*)ptr;
    for (int i = 0; i < size; ++i) {
        *(convert_ptr + i) = 0;
    }
}