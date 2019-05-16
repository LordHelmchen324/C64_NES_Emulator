#include <stdio.h>
#include <stdlib.h>
#include "emu6510.h"
#include "t64.h"

int main(int argc, char* argv[]) {
    State6510* state = (State6510*) malloc(sizeof(State6510));
    state->memory = (uint8_t*) malloc(64000);
    state->s = 0x01ff;

    loadT64TapeToMemory(argv[1], state);

    unsigned char isRunning = 1;
    while (isRunning) {
        emulate6510(state);
    }
    
    return 0;
}