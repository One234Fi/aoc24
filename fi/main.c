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

void execute(int day, int part, char * filepath) {
    switch (day) {
        case 1:
            if (part == 1) {
                day1_part1(filepath);
            } else {
                day1_part2(filepath);
            }
            break;
        default:
            fprintf(stderr, "Invalid input: %d, %d\n", day, part);
    }
}
