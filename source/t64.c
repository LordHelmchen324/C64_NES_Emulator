#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu6510.h"
#include "file.h"

#include "t64.h"

T64Tape* loadT64Tape(char* path) {
    uint8_t* buffer = fileToBuffer(path);
    if (buffer == NULL) return NULL;

    T64Tape* t = (T64Tape*) malloc(sizeof(T64Tape));

    // Header
    memcpy(t->signature, buffer, 32);
    t->version = (int) ((buffer[0x21]<<8) | buffer[0x20]);
    t->maxEntries = (int) ((buffer[0x23]<<8) | buffer[0x22]);
    t->usedEntries = (int) ((buffer[0x25]<<8) | buffer[0x24]);
    memcpy(t->name, &buffer[0x28], 24);

    // Files
    t->entries = (T64Entry*) malloc(sizeof(T64Entry) * t->usedEntries);
    for (int i = 0; i < t->maxEntries; i++) {
        uint8_t* raw = &buffer[0x40 + 0x10 * i];
        t->entries[i].type = raw[0];
        t->entries[i].c64filetype = raw[1];
        t->entries[i].load = (raw[3]<<8) | raw[2];
        t->entries[i].end = (raw[5]<<8) | raw[4];
        t->entries[i].offset = (raw[0x0b]<<24) | (raw[0x0a]<<16) | (raw[9]<<8) | raw[8];
        memcpy(t->entries[i].name, &raw[0x10], 16);
    }
    t->buffer = buffer;

    return t;
}

int loadT64TapeToMemory(char* path, State6510* state) {
    T64Tape* t = loadT64Tape(path);
    if (t == NULL) return 1;

    T64Entry* e = &t->entries[0];
    int datasize = e->end - e->load;
    uint8_t* data = &t->buffer[e->offset];

    memcpy(&state->memory[e->load], data, datasize);

    free(t->entries);
    free(t->buffer);
    free(t);

    return 0;
}

void printT64TapeInfo(T64Tape* t) {
    printf("\n");

    printf("########################################\n");
    printf("Signature:      %s\n", t->signature);
    printf("Version:        $%04x\n", t->version);
    printf("maxEntries:     %d\n", t->maxEntries);
    printf("usedEntries:    %d\n", t->usedEntries);
    printf("Name:           %s\n", t->name);
    printf("########################################\n");

    for (int i = 0; i < t->usedEntries; i++) {
        printf("Entry %02d:       %s\n", i, t->entries[i].name);
        printf("   type         $%02x\n", t->entries[i].type);
        printf("   c64filetype  $%02x\n", t->entries[i].c64filetype);
        printf("   load         $%04x\n", t->entries[i].load);
        printf("   end          $%04x\n", t->entries[i].end);
        printf("   offset       $%08x\n", t->entries[i].offset);
        printf("   -> size      %06d Bytes\n", t->entries[i].end - t->entries[i].load);
        printf("----------------------------------------\n");
    }

    printf("\n");
}