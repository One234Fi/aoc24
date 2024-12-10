#include "trie.h"
#include <stdint.h>

long * set_upsert(long_set ** s, long val, arena * a) {
    for (long i = val; *s; i <<=2) {
        if (val == (*s)->val) {
            return &(*s)->val;
        }
        s = &(*s)->child[i>>62];
    }
    if (!a) {
        return 0;
    }
    *s = new(a, long_set);
    (*s)->val = val;
    return &(*s)->val;
}

long_set ** map_upsert(long_map ** m, long key, arena * a) {
    for (uint64_t i = key; *m; i <<=2) {
        if (key == (*m)->key) {
            return &(*m)->val;
        }
        m = &(*m)->child[i>>62];
    }
    if (!a) {
        return 0;
    }
    *m = new(a, long_map);
    (*m)->key = key;
    return &(*m)->val;
}
