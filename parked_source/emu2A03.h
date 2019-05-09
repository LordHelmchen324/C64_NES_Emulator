#ifndef EMU2A03_H
#define EMU2A03_H

#include <stdint.h>

typedef struct {
    uint8_t c:1;
    uint8_t z:1;
    uint8_t i:1;
    uint8_t d:1;
    uint8_t b:1;
    uint8_t v:1;
    uint8_t n:1;
} StatusRegister2A03;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t* memory;
    uint16_t pc;
    StatusRegister2A03 p;
} State2A03;

void emulate2A03(State2A03* state);
void instructionNotImplementedError(State2A03* state);
void unknownOpcodeError(State2A03* state);

#endif