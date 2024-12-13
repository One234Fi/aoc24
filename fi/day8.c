#include "file.h"
#include "hash.h"
#include "str.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    char f;
} node;

bool node_equal(node a, node b) {
    return a.x == b.x 
        && a.y == b.y 
        && a.f == b.f;
}

typedef struct node_set node_set;
struct node_set {
    node_set * child[4];
    node val;
};

node * node_upsert(node_set ** s, node val, arena * a) {
    for (unsigned long h = hash(val); *s; h <<=2) {
        if (node_equal(val, (*s)->val)) {
            return &(*s)->val;
        }
        s = &(*s)->child[h>>62];
    }
    if (!a) {
        return 0;
    }
    *s = new(a, node_set);
    (*s)->val = val;
    return &(*s)->val;
}


long sum_node_set(node_set * s, string st, int w) {
    if (!s) {
        return 0;
    }
    st.data[w * s->val.y + s->val.x] = '#';
    return 1 + 
        sum_node_set(s->child[0], st, w) +
        sum_node_set(s->child[1], st, w) +
        sum_node_set(s->child[2], st, w) +
        sum_node_set(s->child[3], st, w);
}

typedef struct {
    node * data;
    ptrdiff_t len;
    ptrdiff_t cap;
} vec_node;

void day8_part1(char * filepath) {
    string dat = file_parse(filepath);
    arena perm = arena_init(dat.len * 1024);

    vec_node antennas = {0};

    int y = 0;
    int x = 0;
    for (long i = 0; i < dat.len; i++) {
        if (dat.data[i] == '\n') {
            y++;
            if (x == 0) {
                x = i;
            }
        } else if (dat.data[i] != '.') {
            node n = {0};
            n.x = ((i - y) % x);
            n.y = y;
            n.f = dat.data[i];
            *push(&antennas, &perm) = n;
        }
    }

    node_set * antinodes = 0;

    for (long i = 0; i < antennas.len; i++) {
        for (long j = i; j < antennas.len; j++) {
            node a = antennas.data[i];
            node b = antennas.data[j];
            if (a.f == b.f && i != j) {
                node n = {0};
                if (a.x < b.x) {
                    n.x = a.x - abs(a.x - b.x);
                } else {
                    n.x = a.x + abs(a.x - b.x);
                } 
                if (a.y < b.y) {
                    n.y = a.y - abs(a.y - b.y);
                } else {
                    n.y = a.y + abs(a.y - b.y);
                }
                if (n.x >= 0 && 
                    n.x < x && 
                    n.y >= 0 &&
                    n.y < y) {
                    *node_upsert(&antinodes, n, &perm) = n;
                }

                if (b.x < a.x) {
                    n.x = b.x - abs(a.x - b.x);
                } else {
                    n.x = b.x + abs(a.x - b.x);
                } 
                if (b.y < a.y) {
                    n.y = b.y - abs(a.y - b.y);
                } else {
                    n.y = b.y + abs(a.y - b.y);
                }
                if (n.x >= 0 && 
                    n.x < x && 
                    n.y >= 0 &&
                    n.y < y) {
                    *node_upsert(&antinodes, n, &perm) = n;
                }
            }
        }
    }

    long sum = sum_node_set(antinodes, dat, x);
    fprintf(stdout, "%s\n", dat.data);
    fprintf(stdout, "%ld\n", sum);
}

//
// 5, 2
// 7, 3
//
// 2-3 
//
//
// x = 2d - d


void day8_part2(char * filepath) {
}
