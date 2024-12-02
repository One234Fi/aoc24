#include "str.h"
#include "arena.h"
#include "vector.h"
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
                last = i;
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
