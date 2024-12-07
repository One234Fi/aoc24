#ifndef STR_MODULE_H
#define STR_MODULE_H

#include "arena.h"
#include "vector.h"
#include <stddef.h>

#define make_string(s) (string){(char*)s, sizeof(s)-1}

typedef struct {
    char * data;
    ptrdiff_t len;
} string;

typedef struct {
    string * data;
    ptrdiff_t len;
    ptrdiff_t cap;
} vec_string;

vec_string string_split(arena * a, string s, string delim);
vec_longs parse_longs(arena * a, string s);

#endif
