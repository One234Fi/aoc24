#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include "aoc.h"

void execute(int day, int part, char * filepath);

int main (int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stdout, "usage: aoc <day> <1|2> <filepath>\n");
        exit(EXIT_SUCCESS);
    }
    
    int day = strtol(argv[1], &argv[1], 10);
    int part = strtol(argv[2], &argv[2], 10);
    char* filepath = argv[3];
    
    execute(day, part, filepath);
}

void (*table[][2])(char * filepath) = {
    {
    day1_part1,
    day1_part2,
    },
    {
    day2_part1,
    day2_part2
    },
    {
    day3_part1,
    day3_part2,
    },
    {
    day4_part1,
    day4_part2,
    },
    {
    day5_part1,
    day5_part2,
    },
};

void execute(int day, int part, char * filepath) {
    if (part > 2) {
        part = 2;
    }
    if (part < 1) {
        part = 1;
    }

    int index = day - 1;
    int sub = part - 1;
    table[index][sub](filepath);
}
