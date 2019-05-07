#ifndef EMU6502_H
#define EMU6502_H

#include <stdint.h>

typedef struct {
    uint8_t c:1;
    uint8_t z:1;
    uint8_t i:1;
    uint8_t d:1;
    uint8_t b:1;
    uint8_t v:1;
    uint8_t n:1;
} StatusRegister6502;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t* memory;
    uint16_t pc;
    StatusRegister6502 p;
} State6502;

void emulate6502(State6502* state);
void instructionNotImplementedError(State6502* state);
void unknownOpcodeError(State6502* state);

#endif