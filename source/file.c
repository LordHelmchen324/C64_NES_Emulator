#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

uint8_t* fileToBuffer(char* path) {
    FILE* f = fopen(path, "rb");
    if (f == NULL) return NULL;

    fseek(f, 0L, SEEK_END);
    long int filesize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char* buffer = malloc(filesize);
    fread(buffer, filesize, 1, f);
    fclose(f);

    return buffer;
}