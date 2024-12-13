#include "arena.h"
#include "file.h"
#include "str.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

void day7_part1(char * filepath) {
    arena a = arena_init(1024 * 1024);
    string dat = file_parse(filepath);
    vec_string lines = string_split(&a, dat, make_string("\n"));
    long sum = 0;
    for (long i = 0; i < lines.len; i++) {
        arena t = a;
        vec_longs line = parse_longs(&t, lines.data[i]);
        long test = line.data[0];
        long oplen = line.len - 2;
        long config_count = powl(2, oplen);
        for (long config = 0; config < config_count; config++) {
            long res = line.data[1];
            for (long j = 0; j < oplen; j++) {
                if ((1 << j) & config) {
                    res += line.data[j+2];
                } else {
                    res *= line.data[j+2];
                }
            }
            if (res == test) {
                sum += test;
                break;
            }
        }
    }
    fprintf(stdout, "%ld\n", sum);
}

void day7_part2(char * filepath) {
    arena a = arena_init(1024 * 1024);
    string dat = file_parse(filepath);
    vec_string lines = string_split(&a, dat, make_string("\n"));
    long sum = 0;
    for (long i = 0; i < lines.len; i++) {
        arena t = a;
        vec_longs line = parse_longs(&t, lines.data[i]);
        long test = line.data[0];
        long oplen = line.len - 2;
        long config_count = powl(3, oplen);
        for (long config = 0; config < config_count; config++) {
            long res = line.data[1];
            long bits = config;
            for (long j = 0; j < oplen; j++) {
                switch (bits % 3) {
                    case 0:
                        res += line.data[j+2];
                        break;
                    case 1:
                        res *= line.data[j+2];
                        break;
                    case 2:
                        {
                            long p = 10;
                            long l = line.data[j+2];
                            while (l >= p) {
                                p *= 10;
                            }
                            res *= p;
                            res += l;
                        }
                        break;
                }
                bits /= 3;
            }
            if (res == test) {
                sum += test;
                break;
            }
        }
    }
    fprintf(stdout, "%ld\n", sum);

}
