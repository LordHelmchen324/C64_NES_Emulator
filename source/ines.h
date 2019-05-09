#ifndef INES_H
#define INES_H

#include<stdint.h>

typedef struct {
    char signature[4];
    uint8_t prgsize;
    uint8_t chrsize;
    uint8_t mirroring:1;
    uint8_t hasprgram:1;
    uint8_t hastrainer:1;
    uint8_t ignoremirroring:1;
    uint8_t mapper;
    uint8_t isvsunisystem:1;
    uint8_t haspc10:1;
    uint8_t isnes2:1;
    uint8_t* trainer;
    uint8_t* prg;
    uint8_t* chr;
    uint8_t* pcir;
    uint8_t* pcpr;
} iNES;

#endif