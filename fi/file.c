#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

string file_parse(char * filepath) {
    FILE * f = fopen(filepath, "rb");
    if (!f) {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0L, SEEK_END);
    ptrdiff_t size = 0;
    size = ftell(f);
    if (size < 0) {
        fprintf(stderr, "Failed to parse file length\n");
        exit(EXIT_FAILURE);
    } else if (size == 0) {
        fprintf(stderr, "File is empty\n");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0L, SEEK_SET);

    string s = {0};
    s.data = malloc(size);
    s.len = size;

    int res = fread(s.data, 1, size, f);
    if (res != size) {
        fprintf(stderr, "Failed to parse file contents\n");
        exit(EXIT_FAILURE);
    }
    
    fclose(f);

    return s;
}

