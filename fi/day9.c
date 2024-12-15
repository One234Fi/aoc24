#include "arena.h"
#include "file.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>


void day9_part1(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 128);
    bool block = 1;
    vec_longs uncompressed = {0};
    long id = 0;
    for (long i = 0; i < dat.len; i++) {
        long dist = dat.data[i] - '0';
        if (block) {
            for (int j = 0; j < dist; j++) {
                *push(&uncompressed, &a) = id;
            }
            id++;
        } else {
            for (int j = 0; j < dist; j++) {
                *push(&uncompressed, &a) = -1;
            }
        }
        block = !block;
    }

    long compressed[uncompressed.len] = {};
    long len = 0;
    long back = uncompressed.len-1;
    for (long i = 0; i <= back; i++) {
        if (uncompressed.data[i] == -1) {
            compressed[i] = uncompressed.data[back];
            do {
                back--;
            } while (uncompressed.data[back] == -1);
        } else {
            compressed[i] = uncompressed.data[i];
        }
        len++;
    }

    long sum = 0;
    for (long i = 0; i < len; i++) {
        sum += compressed[i] * i;
    }
    fprintf(stdout, "%ld\n", sum);
}

void day9_part2(char * filepath) {
}
