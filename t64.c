#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#include "t64.h"

T64Tape* loadT64Tape(char* path) {
    uint8_t* buffer = fileToBuffer(path);
    if (buffer == NULL) return NULL;

    T64Tape* t = malloc(sizeof(T64Tape));
    memcpy(t->signature, buffer, 32);
    t->version = (int) ((buffer[0x21] << 8) | buffer[0x20]);
    t->maxEntries = (int) ((buffer[0x23] << 8) | buffer[0x22]);
    t->usedEntries = (int) ((buffer[0x25] << 8) | buffer[0x24]);
    memcpy(t->name, &buffer[0x28], 24);

    free(buffer);

    return t;
}