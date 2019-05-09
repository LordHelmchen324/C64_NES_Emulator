#include <stdio.h>
#include <stdlib.h>
#include "ines.h"

int main(int argc, char* argv[]) {
    iNES* ines = loadiNES(argv[1]);

    printiNESInfo(ines);

    /*State6510* state = (State6510*) malloc(sizeof(State6510));
    state->memory = (uint8_t*) malloc(64000);

    loadT64TapeToMemory(argv[1], state);

    unsigned char isRunning = 1;
    while (isRunning) {
        emulate6510(state);
    }*/
    
    return 0;
}