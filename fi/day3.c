#include "aoc.h"
#include "file.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

long parse_mul(char ** ptr) {
    char * p = *ptr;
    if (strncmp(p, "mul(", 4) == 0) {
        p+=4;
        if (isdigit(*p)) {
            long a = strtol(p, &p, 10);

            if (*p == ',') {
                p++;
                if (isdigit(*p)) {
                    long b = strtol(p, &p, 10);

                    if (*p == ')') {
                        *ptr = p;
                        return a * b;
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

void parse_do(char ** ptr, bool * flag) {
    if (strncmp(*ptr, "don't()", 7) == 0) {
        *ptr += 6;
        *flag = false;
    } else if (strncmp(*ptr, "do()", 4) == 0) {
        *ptr += 3;
        *flag = true;
    }  
    *ptr += 1;
}
    

void day3_part2(char *filepath) {
    string dat = file_parse(filepath);
    long sum = 0;

    char * p = dat.data;
    char * curr = p;
    bool should_parse = true;
    while (p - dat.data < dat.len) {
        if (*p == 'm' && should_parse) {
            sum += parse_mul(&p);
        } else if (*p == 'd') {
            parse_do(&p, &should_parse);
        } else {
            p++;
        }
    }
    
    fprintf(stdout, "%ld\n", sum);
}


