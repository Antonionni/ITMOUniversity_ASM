#include "mem.h"

void memalloc_debug_struct_info(FILE* f, MemType const* const address ) {
    size_t i;
    fprintf(f, "start: %p\nsize: %lu\nis_free: %d\n", (void*)address, address->capacity, address->is_free );
    for (i = 0; i < DEBUG_FIRST_BYTES && i < address->capacity; ++i )
        fprintf( f, "%hhX", ((char*)address)[ sizeof(MemType) + i ] );
    putc('\n', f );
}
void memalloc_debug_heap(FILE* f, MemType const* ptr ) {
    for(; ptr; ptr = ptr->next) {
        memalloc_debug_struct_info(f, ptr);
    }
}