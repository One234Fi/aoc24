#include "arena.h"
#include "file.h"
#include "str.h"
#include <stdio.h>
#include <stdbool.h>

#define left (x > 2)
#define right (x < lines.data[y].len - 3)
#define up (y > 2)
#define down (y < lines.len - 3)
#define get(x, y) lines.data[y].data[x]

#define checkx(dirx) (\
        get(x, y) == 'X' && \
        get(x dirx 1, y) == 'M' && \
        get(x dirx 2, y) == 'A' && \
        get(x dirx 3, y) == 'S')

#define checky(diry) (\
        get(x, y) == 'X' && \
        get(x, y diry 1) == 'M' && \
        get(x, y diry 2) == 'A' && \
        get(x, y diry 3) == 'S')

#define checkxy(dirx, diry) (\
        get(x, y) == 'X' && \
        get(x dirx 1, y diry 1) == 'M' && \
        get(x dirx 2, y diry 2) == 'A' && \
        get(x dirx 3, y diry 3) == 'S')

void day4_part1(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 4);
    vec_string lines = string_split(&a, dat, make_string("\n"));
    long sum = 0;
    for (ptrdiff_t y = 0; y < lines.len; y++) {
        for (ptrdiff_t x = 0; x < lines.data[y].len; x++) {
            if (left && down && checkxy(-, +)) {
                sum++; 
                fprintf(stdout, "left down: %ld, %ld\n", x, y);
            }
            if (left && checkx(-)) {
                sum++; 
                fprintf(stdout, "left: %ld, %ld\n", x, y);
            }
            if (left && up && checkxy(-, -)) {
                sum++; 
                fprintf(stdout, "left up: %ld, %ld\n", x, y);
            }
            if (up && checky(-)) {
                sum++; 
                fprintf(stdout, "up: %ld, %ld\n", x, y);
            }
            if (right && up && checkxy(+, -)) {
                sum++; 
                fprintf(stdout, "right up: %ld, %ld\n", x, y);
            }
            if (right && checkx(+)) {
                sum++; 
                fprintf(stdout, "right: %ld, %ld\n", x, y);
            }
            if (right && down && checkxy(+, +)) {
                sum++; 
                fprintf(stdout, "right down: %ld, %ld\n", x, y);
            }
            if (down && checky(+)) {
                sum++; 
                fprintf(stdout, "down: %ld, %ld\n", x, y);
            }
        }
    }

    fprintf(stdout, "%ld\n", sum);
}

void day4_part2(char * filepath) {
    string dat = file_parse(filepath);
    arena a = arena_init(dat.len * 4);
    vec_string lines = string_split(&a, dat, make_string("\n"));
    long sum = 0;
    for (ptrdiff_t y = 1; y < lines.len-1; y++) {
        for (ptrdiff_t x = 1; x < lines.data[y].len-1; x++) {
            bool mida = get(x, y) == 'A';

            bool mas1 = (
                    get(x-1, y-1) == 'M' &&
                    get(x+1, y+1) == 'S'
                    ) || (
                    get(x-1, y-1) == 'S' &&
                    get(x+1, y+1) == 'M'
                    );
            bool mas2 = (
                    get(x+1, y-1) == 'M' &&
                    get(x-1, y+1) == 'S'
                    ) || (
                    get(x+1, y-1) == 'S' &&
                    get(x-1, y+1) == 'M'
                    );

            if (mida && mas1 && mas2) {
                sum++;
                fprintf(stdout, "%ld, %ld\n", x, y);
            }
        }
    }

    fprintf(stdout, "%ld\n", sum);
}
