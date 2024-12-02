#include "aoc.h"
#include "arena.h"
#include "file.h"
#include "str.h"
#include "vector.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int compare_longs(const void * a, const void * b) {
    return (*(long *)a - *(long *)b);
}

long sum(vec_longs vec) {
    long sum = 0;
    for (ptrdiff_t i = 0; i < vec.len; i++) {
        sum += vec.data[i];
    }
    return sum;
}

void day1_part1(char *filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * sizeof(string) * 4);
    vec_string lines = string_split(&a, dat, make_string("\n"));

    vec_longs left = {0};
    vec_longs right = {0};
    for (ptrdiff_t i = 0; i < lines.len; i++) {
        char * p = lines.data[i].data;
        *push(&left, &a) = strtol(p, &p, 10);
        *push(&right, &a) = strtol(p, &p, 10);
    }

    qsort(left.data, left.len, sizeof(long), compare_longs);
    qsort(right.data, right.len, sizeof(long), compare_longs);

    vec_longs diffs = left;
    for (ptrdiff_t i = 0; i < diffs.len; i++) {
        diffs.data[i] = labs(left.data[i] - right.data[i]);
    }

    fprintf(stdout, "SUM: %ld\n", sum(diffs));

    free(dat.data);
}
