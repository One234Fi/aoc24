#include "hash.h"

unsigned long fnv_1a_hash(void * val, ptrdiff_t size) { 
    unsigned long h = 0xcbf29ce484222325;
    char * p = (char*)val;
    for (int i = 0; i < size; i++) {
        h ^= (unsigned long)(p[i]);
        h *= 0x100000001b3;
    }
    return h;
}
