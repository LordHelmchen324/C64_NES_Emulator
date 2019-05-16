#ifndef EMU6510_H
#define EMU6510_H

#include <stdint.h>

typedef struct {
    uint8_t c:1;    // CARRY         1 = TRUE
    uint8_t z:1;    // ZERO          1 = RESULT ZERO
    uint8_t i:1;    // IRQ DISABLE   1 = DISABLE
    uint8_t d:1;    // DECIMAL MODE  1 = TRUE
    uint8_t b:1;    // BRK COMMAND
    uint8_t v:1;    // OVERFLOW      1 = TRUE
    uint8_t n:1;    // NEGATIVE      1 = NEG
} StatusRegister6510;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t* memory;
    uint16_t pc;
    uint16_t s;
    StatusRegister6510 p;
} State6510;

void emulate6510(State6510* state);
void instructionNotImplementedError(State6510* state);
void unknownOpcodeError(State6510* state);
void printState6510(State6510* state);

#endif