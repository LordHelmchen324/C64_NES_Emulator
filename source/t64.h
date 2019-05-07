#ifndef T64_H
#define T64_H

typedef struct {
    uint8_t type;
    uint8_t c64filetype;
    uint16_t load;
    uint16_t end;
    uint32_t offset;
    char name[16];
    uint8_t* data;
} T64Entry;

typedef struct {
    char signature[32];
    int version;
    char name[24];
    int maxEntries;
    int usedEntries;
    T64Entry* entries;
} T64Tape;

T64Tape* loadT64Tape(char* path);
uint8_t* programFromT64Tape(T64Tape* t);
void printT64TapeInfo(T64Tape* t);

#endif