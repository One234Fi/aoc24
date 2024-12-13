#ifndef TRIE_MODULE_H
#define TRIE_MODULE_H

#include "arena.h"

typedef struct long_set long_set;
struct long_set {
    long_set * child[4];
    long val;
};

long * set_upsert(long_set ** s, long val, arena * a);


typedef struct long_map long_map;
struct long_map {
    long_map * child[4];
    long key;
    long_set * val;
};

long_set ** map_upsert(long_map ** m, long key, arena * a);


#endif
