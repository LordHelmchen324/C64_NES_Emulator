#include <stdio.h>
#include <stdlib.h>
#include "disassembler.h"
#include "t64.h"

int main(int argc, char* argv[]) {
    T64Tape* t = loadT64Tape(argv[1]);
    if (t == NULL) {
        printf("ERROR: Could not load file %s\n", argv[1]);
        exit(1);
    }

    printT64TapeInfo(t);

    uint8_t* prg = programFromT64Tape(t);
    int pc = 0;
    while (pc < 100) {
        pc += disassemble6502(prg, pc);
    }
    
    return 0;
}