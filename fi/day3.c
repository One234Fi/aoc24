#include "aoc.h"
#include "file.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long parse_mul(char ** ptr) {
    char * p = *ptr;
    if (strncmp(p, "mul(", 4) == 0) {
        p+=4;
        if (isdigit(*p)) {
            long a = strtol(p, &p, 10);
            fprintf(stdout, "parsed a: %ld\n", a);

            if (*p == ',') {
                p++;
                if (isdigit(*p)) {
                    long b = strtol(p, &p, 10);
                    fprintf(stdout, "parsed b: %ld\n", b);

                    if (*p == ')') {
                        *ptr = p;
                        return a * b;
                        fprintf(stdout, "adding: %ld\n", a * b);
                    }
                }
            }
        } else {
            p++;
        }
    } else {
        p++;
    }
    *ptr = p;
    return 0;
}


void day3_part1(char *filepath) {
    string dat = file_parse(filepath);
    long sum = 0;

    char * p = dat.data;
    char * curr = p;
    while (p - dat.data < dat.len) {
        if (*p == 'm') {
            sum += parse_mul(&p);
        } else {
            p++;
        }
    }
    
    fprintf(stdout, "%ld\n", sum);
}

void day3_part2(char *filepath) {
}


