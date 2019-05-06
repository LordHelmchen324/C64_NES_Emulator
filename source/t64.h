#ifndef T64_H
#define T64_H

typedef struct {
    char signature[32];
    int version;
    int maxEntries;
    int usedEntries;
    char name[24];
} T64Tape;

T64Tape* loadT64Tape(char* path);

#endif