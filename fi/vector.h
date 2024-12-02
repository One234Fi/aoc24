#ifndef VECTOR_MODULE
#define VECTOR_MODULE

/* vector definition
 *
 *  struct {
 *      void * data;
 *      ptrdiff_t len;
 *      ptrdiff_t cap;
 *  };
 */

#include "arena.h"
#include <assert.h>
#include <stddef.h>

void grow(void * slice, ptrdiff_t size, arena * a);

#define push(s, arena)  ((s)->len >= (s)->cap ? grow(s, sizeof(*(s)->data), arena), (s)->data + (s)->len++ : (s)->data + (s)->len++) 

typedef struct {
    long * data;
    ptrdiff_t len;
    ptrdiff_t cap;
} vec_longs;

#endif
