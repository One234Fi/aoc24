#ifndef HASH_MODULE_H
#define HASH_MODULE_H

#include <stddef.h>

#define hash(val) fnv_1a_hash(&val, sizeof(val))

unsigned long fnv_1a_hash(void * val, ptrdiff_t size);


#endif
