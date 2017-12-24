#include <stdio.h>
#include "mem.h"

int main() {
    FILE *file = fopen("text.txt", "r");
    MemType *mem_object;
    memalloc_debug_heap(file, mem_object);
    return 0;
}