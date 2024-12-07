#include "arena.h"
#include "file.h"
#include "str.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool is_safe(vec_longs report) {
    bool ascend = false;
    bool descend = false;
    bool adjacency_violation = false;

    vec_longs diffs = {0};
    for (ptrdiff_t i = 0; i < report.len-1; i++) {
        long diff = report.data[i] - report.data[i+1];
        if (diff < 0) {
            descend = true;
        } else if (diff > 0) {
            ascend = true;
        }

        diff = labs(diff);
        if (diff < 1 || diff > 3) {
            return false;
        }
    }

    if (ascend && !descend) {
        return true;
    }
    if (descend && !ascend) {
        return true;
    }

    return false;
}

void day2_part1(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 4);
    vec_string lines = string_split(&a, dat, make_string("\n"));

    long sum = 0;
    for (ptrdiff_t i = 0; i < lines.len; i++) {
        arena scratch = a;
        vec_longs report = parse_longs(&scratch, lines.data[i]);
        bool safe = is_safe(report);

        if (safe) {
            sum++;
        }
    }

    fprintf(stdout, "%ld\n", sum);
}

