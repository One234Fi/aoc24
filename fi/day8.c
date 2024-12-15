#include "file.h"
#include "hash.h"
#include "str.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    char f;
} node;

typedef struct head head;
struct head {
    head * next;
    node * val;
};

bool node_equal(node a, node b) {
    return a.x == b.x 
        && a.y == b.y ;
}

typedef struct node_set node_set;
struct node_set {
    node_set * child[4];
    node val;
};

node * node_upsert(node_set ** s, node val, head ** list, arena * a) {
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
    if (!!list) {
        head * l = new(a, head);
        l->val = &(*s)->val;
        l->next = *list;
        *list = l;
    }
    return &(*s)->val;
}

long sum_node_set(node_set * s) {
    if (!s) {
        return 0;
    }
    return 1 + 
        sum_node_set(s->child[0]) +
        sum_node_set(s->child[1]) +
        sum_node_set(s->child[2]) +
        sum_node_set(s->child[3]);
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
                    *node_upsert(&antinodes, n, NULL, &perm) = n;
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
                    *node_upsert(&antinodes, n, NULL, &perm) = n;
                }
            }
        }
    }

    long sum = sum_node_set(antinodes);
    fprintf(stdout, "%s\n", dat.data);
    fprintf(stdout, "%ld\n", sum);
}

node make_antinode(node a, node b) {
    node n = {0};
    n.x = 2 * b.x - a.x;
    n.y = 2 * b.y - a.y;
    return n;
}

#define get(g, x_p, y_p) g.data[y_p * g.x + x_p]
#define in_bounds(g, x_p, y_p) (x_p >= 0 && y_p >= 0 && x_p < g.x && y_p < g.y)
typedef struct {
    char * data;
    int x;
    int y;
} grid;

grid new_grid(arena * a, int x, int y) {
    grid g = {0};
    g.data = new(a, char, x * y);
    memset(g.data, '.', x * y);
    g.x = x;
    g.y = y;
    return g;
}

void print_grid(grid g, arena scratch) {
    char * buf = new(&scratch, char, g.x + 1);
    for (int i = 0; i < g.y; i++) {
        memcpy(buf, g.data + (i * g.x), g.x);
        buf[g.x] = '\0';
        fprintf(stdout, "%s\n", buf);
    }
}

void generate_antinodes(node a, node b, arena * perm, node_set **s, grid g) {
    if (in_bounds(g, a.x, a.y)) {
        get(g, a.x, a.y) = '#';
        fprintf(stdout, "%d, %d\n", a.x, a.y);
    }

    node n = make_antinode(a, b);
    if (in_bounds(g, n.x, n.y)) {
        get(g, n.x, n.y) = '#';
    }

    node at = b;
    node bt = n;
    while(in_bounds(g, n.x, n.y)) {
        n = make_antinode(at, bt);
        if (in_bounds(g, n.x, n.y)) {
            get(g, n.x, n.y) = '#';
        }
        at = bt;
        bt = n;
    }
}

void day8_part2(char * filepath) {
    string dat = file_parse(filepath);
    arena perm = arena_init(dat.len * 1024 * 2);

    vec_string lines = string_split(&perm, dat, make_string("\n"));
    node_set * antennas = 0;
    head * list = new(&perm, head);

    grid g = new_grid(&perm, lines.data[0].len, lines.len);
    for (long y = 0; y < lines.len; y++) {
        for (long x = 0; x < lines.data[y].len; x++) {
            if (lines.data[y].data[x] != '.' && 
                lines.data[y].data[x] != '\n') {
                node n = {0};
                n.x = x;
                n.y = y;
                n.f = lines.data[y].data[x];
                *node_upsert(&antennas, n, &list, &perm) = n;
            }
        }
    }

    node_set * antinodes = 0;

    for (head * i = list; i->next != NULL; i = i->next) {
        for (head * j = list; j->next != NULL; j = j->next) {
            node a = *i->val;
            node b = *j->val;
            if (a.f == b.f && i != j) {
                generate_antinodes(b, a, &perm, &antinodes, g);
                generate_antinodes(a, b, &perm, &antinodes, g);
            }
        }
    }

    long sum = 0;
    for (long i = 0; i < g.x * g.y; i++) {
        if (g.data[i] != '.') {
            sum++;
        }
    }
    print_grid(g, perm);
    fprintf(stdout, "%ld\n", sum);
}
