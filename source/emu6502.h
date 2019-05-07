#ifndef EMU6502_H
#define EMU6502_H

#include <stdint.h>

typedef struct {
    uint8_t bla;
} ConditionCodes6502;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t* memory;
    uint8_t pc;
    ConditionCodes6502 cc;
} State6502;

void emulate6502(State6502* state);
void instructionNotImplementedError(State6502* state);
void unknownOpcodeError(State6502* state);

#endif