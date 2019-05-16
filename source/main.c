#include <stdio.h>
#include <stdlib.h>
#include "emu6510.h"
#include "t64.h"

int main(int argc, char* argv[]) {
    State6510* state = makeState6510Default();

    loadT64TapeToMemory(argv[1], state);

    unsigned char isRunning = 1;
    while (isRunning) {
        emulate6510(state);
    }
    
    return 0;
}