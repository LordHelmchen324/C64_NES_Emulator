#ifndef INES
#define INES

#include<stdint.h>

typedef struct {
    int prgsize;
    uint8_t* prg;
    int chrsize;
    uint8_t* chr;
} INESCartridge;

#endif