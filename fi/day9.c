#include "arena.h"
#include "file.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

typedef struct file file;
struct file {
    long id;
    long len;
    bool empty;
    file * next;
};

void day9_part2(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 128);
    bool block = 1;
    long id = 0;
    file * files = new(&a, file);
    for (long i = 0; i < dat.len; i++) {
        long dist = dat.data[i] - '0';
        if (block) {
            file * f = new(&a, file);
            f->id = id++;
            f->empty = false;
            f->len = dist;
            file * t = files;
            while (t->next != NULL) {
                t = t->next;
            }
            t->next = f;
        } else {
            file * f = new(&a, file);
            f->len = dist;
            f->empty = true;
            file * t = files;
            while (t->next != NULL) {
                t = t->next;
            }
            t->next = f;
        }
        block = !block;
    }

    file * filestack [id];
    long top = 0;
    for (file* f = files; f->next != NULL; f = f->next) {
        if (!f->empty) {
            filestack[top++] = f;
        }
    }

    for (long i = top; i >= 0; i--) {
        file * r = filestack[i];
        for (file* f = files; f->next != NULL; f = f->next) {
            if (f->id == r->id) {
                break;
            } else if (r->len == f->len && f->empty && !r->empty) {
                f->id = r->id;
                f->empty = false;
                r->empty = true;
                r->id = 0;
                break;
            } else if (r->len < f->len && f->empty && !r->empty) {
                file * n = new(&a, file);
                n->id = 0;
                n->len = f->len - r->len;
                n->empty = true;
                n->next = f->next;

                f->empty = false;
                f->len = r->len;
                f->id = r->id;
                f->next = n;

                r->empty = true;
                r->id= 0;
                break;
            }
        }
    }

    vec_longs res = {0};
    for (file* f = files; f->next != NULL; f = f->next) {
        for (long i = 0; i < f->len; i++) {
            *push(&res, &a) = f->id;
        }
    }

    long sum = 0;
    for (long i = 0; i < res.len; i++) {
        sum += i * res.data[i];
    }
    fprintf(stdout, "%ld\n", sum);
} 
