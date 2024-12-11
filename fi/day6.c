#include "aoc.h"
#include "arena.h"
#include "str.h"
#include "file.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    long x;
    long y;
    bool oob;
} pos;

#define get(g, x, y) g.data[y].data[x]

pos scan_up(vec_string grid, pos p) {
    long x = p.x;
    char land = 0;
    for (long y = p.y; y >= 0; y--) {
        land = get(grid, x, y);
        if (land == '#') {
            pos n = {0};
            n.x = x;
            n.y = y+1;
            return n;
        }
        grid.data[y].data[x] = 'X';
    }

    pos n = {0};
    n.x = x;
    n.y = 0;
    n.oob = true;
    return n;
}

pos scan_down(vec_string grid, pos p) {
    long x = p.x;
    char land = 0;
    for (long y = p.y; y < grid.len; y++) {
        land = get(grid, x, y);
        if (land == '#') {
            pos n = {0};
            n.x = x;
            n.y = y-1;
            return n;
        }
        grid.data[y].data[x] = 'X';
    }

    pos n = {0};
    n.x = x;
    n.y = grid.len-1;
    n.oob = true;
    return n;
}

pos scan_left(vec_string grid, pos p) {
    long y = p.y;
    char land = 0;
    for (long x = p.x; x >= 0; x--) {
        land = get(grid, x, y);
        if (land == '#') {
            pos n = {0};
            n.x = x+1;
            n.y = y;
            return n;
        }
        grid.data[y].data[x] = 'X';
    }

    pos n = {0};
    n.x = 0;
    n.y = y;
    n.oob = true;
    return n;
}

pos scan_right(vec_string grid, pos p) {
    long y = p.y;
    char land = 0;
    for (long x = p.x; x < grid.data[y].len; x++) {
        land = get(grid, x, y);
        if (land == '#') {
            pos n = {0};
            n.x = x-1;
            n.y = y;
            return n;
        }
        grid.data[y].data[x] = 'X';
    }

    pos n = {0};
    n.x = grid.data[y].len-1;
    n.y = y;
    n.oob = true;
    return n;
}

long sum_travel(string dat) {
    long sum = 0;
    for (long i = 0; i < dat.len; i++) {
        if (dat.data[i] == 'X') {
            sum++;
        }
    }
    return sum;
}

pos find_start(vec_string grid) {
    pos p = {0};
    p.x = -1;
    p.y = -1;
    for (long y = 0; y < grid.len; y++) {
        for (long x = 0; x < grid.data[y].len; x++) {
            if (get(grid, x, y) == '^') {
                p.x = x;
                p.y = y;
                return p;
            }
        }
    }
    return p;
}

void day6_part1(char *filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 8);
    vec_string grid = string_split(&a, dat, make_string("\n"));
    pos p = find_start(grid);
    if (p.x == -1 || p.y == -1) {
        fprintf(stdout, "failed to find the guard\n");
    }
    int dir = 0;
    while (!p.oob) {
        switch(dir) {
            case 0: p = scan_up(grid, p); break;
            case 1: p = scan_right(grid, p); break;
            case 2: p = scan_down(grid, p); break;
            case 3: p = scan_left(grid, p); break;
            default: 
                fprintf(stdout, "invalid scan state\n");
        }
        dir = (dir + 1) % 4;
    }
    fprintf(stdout, "%s", dat.data);
    long sum = sum_travel(dat);
    fprintf(stdout, "%ld\n", sum);
}

void day6_part2(char *filepath) {
}
