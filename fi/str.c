#include "str.h"
#include "arena.h"
#include "vector.h"
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

vec_string string_split(arena * a, string s, string delim) {
    vec_string v = {0};

    ptrdiff_t last = 0;
    for (ptrdiff_t i = 0; i < s.len; i++) {
        if (s.len - i >= delim.len) {
            if (strncmp(s.data + i, delim.data, delim.len) == 0) {
                string n = {0};
                n.data = s.data + last;
                n.len = i - last;
                last = i + 1;
                *push(&v, a) = n;
            }
        } else {
            string n = {0};
            n.data = s.data + last;
            n.len = i - last;
            *push(&v, a) = n;
        }
    }

    return v;
}

vec_longs parse_longs(arena * a, string s) {
    vec_longs v = {0};

    char * c = s.data;
    while ((*c) != '\n') {
        if (isdigit(*c)) {
            long l = strtol(c, &c, 10);
            *push(&v, a) = l;
        } else {
            c++;
        }
    }

    return v;
}
