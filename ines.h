#ifndef INES_H
#define INES_H

#include<stdint.h>

typedef struct {
    int prgsize;
    uint8_t* prg;
    int chrsize;
    uint8_t* chr;
} INESCartridge;

#endif