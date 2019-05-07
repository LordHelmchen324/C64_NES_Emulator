#include <stdio.h>
#include <stdlib.h>
#include "emu6502.h"
#include "t64.h"

int main(int argc, char* argv[]) {
    T64Tape* t = loadT64Tape(argv[1]);
    if (t == NULL) {
        printf("ERROR: Could not load file %s\n", argv[1]);
        exit(1);
    }

    printT64TapeInfo(t);

    return 0;
}