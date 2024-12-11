#include "arena.h"
#include "str.h"
#include "file.h"
#include "trie.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool do_before_rules(long_set **rules, vec_longs manual, ptrdiff_t index) {
    if ((*rules) && (index-1 < manual.len)) {
        long l = (*rules)->val;
        for (ptrdiff_t i = index; i < manual.len; i++) {
            if (manual.data[i] == l) {
                return false;
            }
        }
        return 
            do_before_rules(&(*rules)->child[0], manual, index) &&
            do_before_rules(&(*rules)->child[1], manual, index) &&
            do_before_rules(&(*rules)->child[2], manual, index) &&
            do_before_rules(&(*rules)->child[3], manual, index)
            ;
    }
    return true;
}

bool do_after_rules(long_set **rules, vec_longs manual, ptrdiff_t index) {
    if ((*rules) && (index > 0)) {
        long l = (*rules)->val;
        for (ptrdiff_t i = 0; i < index; i++) {
            if (manual.data[i] == l) {
                return false;
            }
        }
        return 
            do_after_rules(&(*rules)->child[0], manual, index) &&
            do_after_rules(&(*rules)->child[1], manual, index) &&
            do_after_rules(&(*rules)->child[2], manual, index) &&
            do_after_rules(&(*rules)->child[3], manual, index)
            ;
    }
    return true;
}

void day5_part1(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 32);
    vec_string lines = string_split(&a, dat, make_string("\n"));

    long_map * before_rules = 0;
    long_map * after_rules = 0;
    ptrdiff_t i = 0;
    string line = lines.data[i];
    while (line.data[0] != '\n') { //go till empty line
        vec_longs rule = parse_longs(&a, lines.data[i]);
        long_set ** set = map_upsert(&before_rules, rule.data[1], &a);
        set_upsert(set, rule.data[0], &a);
        set = map_upsert(&after_rules, rule.data[0], &a);
        set_upsert(set, rule.data[1], &a);
        i++;
        line = lines.data[i];
    }
    i++; //skip empty line

    long sum = 0;
    for (; i < lines.len; i++) {
        arena scratch = a;
        vec_longs manual = parse_longs(&scratch, lines.data[i]);
        bool valid = true;
        for (ptrdiff_t j = 0; j < manual.len; j++) {
            long key = manual.data[j];
            long_set ** brules = map_upsert(&before_rules, key, NULL);
            if (brules && !do_before_rules(brules, manual, j)) {
                valid = false;
            }
            long_set ** arules = map_upsert(&after_rules, key, NULL);
            if (arules && !do_after_rules(arules, manual, j)) {
                valid = false;
            }
        }

        if (valid) {
            sum += manual.data[manual.len / 2];
        }
    }

    fprintf(stdout, "%ld\n", sum);
}



long_map * ltr = 0;

int compare(const void * a, const void * b) {
    long al = *(long *) a; 
    long bl = *(long *) b; 

    long_set ** s = map_upsert(&ltr, al, NULL);
    if (!!s) {
        long * res = set_upsert(s, bl, NULL);
        if (!!res) {
            return -1;
        }
    }

    s = map_upsert(&ltr, bl, NULL);
    if (!!s) {
        long * res = set_upsert(s, al, NULL);
        if (!!res) {
            return 1;
        }
    }

    return 0;
}

bool is_ordered(vec_longs manual) {
    for (ptrdiff_t i = 0; i < manual.len; i++) {
        for (ptrdiff_t j = i; j < manual.len; j++) {
            if (i == j) {
                continue;
            }
            if (compare(&manual.data[i], &manual.data[j]) == 1) {
                return false;
            }
        }
    }
    return true;
}

void day5_part2(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 32);
    vec_string lines = string_split(&a, dat, make_string("\n"));

    ptrdiff_t i = 0;
    string line = lines.data[i];
    while (line.data[0] != '\n') { //go till empty line
        vec_longs rule = parse_longs(&a, lines.data[i]);
        long_set ** set = map_upsert(&ltr, rule.data[0], &a);
        set_upsert(set, rule.data[1], &a);
        i++;
        line = lines.data[i];
    }
    i++; //skip empty line

    long sum = 0;
    for (; i < lines.len; i++) {
        arena scratch = a;
        vec_longs manual = parse_longs(&scratch, lines.data[i]);
        if (!is_ordered(manual)) {
            qsort(manual.data, manual.len, sizeof(manual.data[i]), compare);
            sum += manual.data[manual.len / 2];
        }
    }

    fprintf(stdout, "%ld\n", sum);
} 
