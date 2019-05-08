#ifndef EMU6510_H
#define EMU6510_H

#include <stdint.h>

typedef struct {
    uint8_t c:1;
    uint8_t z:1;
    uint8_t i:1;
    uint8_t d:1;
    uint8_t b:1;
    uint8_t v:1;
    uint8_t n:1;
} StatusRegister6510;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t* memory;
    uint16_t pc;
    StatusRegister6510 p;
} State6510;

void emulate6510(State6510* state);
void instructionNotImplementedError(State6510* state);
void unknownOpcodeError(State6510* state);

#endif