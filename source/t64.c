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

    // Header
    memcpy(t->signature, buffer, 32);
    t->version = (int) ((buffer[0x21]<<8) | buffer[0x20]);
    t->maxEntries = (int) ((buffer[0x23]<<8) | buffer[0x22]);
    t->usedEntries = (int) ((buffer[0x25]<<8) | buffer[0x24]);
    memcpy(t->name, &buffer[0x28], 24);

    // Files
    t->entries = malloc(sizeof(T64Entry) * t->usedEntries);
    for (int i = 0; i < t->maxEntries; i++) {
        uint8_t* raw = &buffer[0x40 + 0x10 * i];
        t->entries[i].filetypec64s = raw[0];
        t->entries[i].filetype1541 = raw[1];
        t->entries[i].load = (raw[3]<<8) | raw[2];
        t->entries[i].end = (raw[5]<<8) | raw[4];
        t->entries[i].offset = (raw[0x0b]<<24) | (raw[0x0a]<<16) | (raw[9]<<8) | raw[8];
        memcpy(t->entries[i].name, &raw[0x10], 16);
        t->entries[i].data = NULL;
    }

    free(buffer);

    return t;
}