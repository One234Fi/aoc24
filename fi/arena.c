#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"

arena
arena_init(ptrdiff_t cap) {
    arena a = {0};
    a.beg = malloc(cap);
    a.end = a.beg ? a.beg + cap : 0;
    return a;
}

void * 
alloc(arena * a, ptrdiff_t size, ptrdiff_t align, ptrdiff_t count) {
    assert(size != 0);
    ptrdiff_t padding = -(uintptr_t)a->beg & (align - 1);
    ptrdiff_t available = a->end - a->beg - padding;
    if (available < 0 || count > available / size) {
        fprintf(stderr, "Arena out of memory\n");
        exit(EXIT_FAILURE);
    }
    void * p = a->beg + padding;
    a->beg += padding + count * size;
    return memset(p, 0, count * size);
}
