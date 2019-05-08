#include <stdio.h>
#include <stdlib.h>

#include "emu2A03.h"

void emulate2A03(State2A03* state) {
    unsigned char* opcode = &state->memory[state->pc];

    switch (*opcode) {
        case 0x00: instructionNotImplementedError(state); break;    // BRK
        case 0x01: instructionNotImplementedError(state); break;    // ORA ($NN,X)
        case 0x05: instructionNotImplementedError(state); break;    // ORA $NN
        case 0x06: instructionNotImplementedError(state); break;    // ASL $NN
        case 0x08: instructionNotImplementedError(state); break;    // PHP
        case 0x09: instructionNotImplementedError(state); break;    // ORA #$NN
        case 0x0a: instructionNotImplementedError(state); break;    // ASL A
        case 0x0d: instructionNotImplementedError(state); break;    // ORA $NNNN
        case 0x0e: instructionNotImplementedError(state); break;    // ASL $NNNN
        case 0x10: instructionNotImplementedError(state); break;    // BPL $NN
        case 0x11: instructionNotImplementedError(state); break;    // ORA ($NN),Y
        case 0x15: instructionNotImplementedError(state); break;    // ORA $NN,X
        case 0x16: instructionNotImplementedError(state); break;    // ASL $NN,X
        case 0x18: instructionNotImplementedError(state); break;    // CLC
        case 0x19: instructionNotImplementedError(state); break;    // ORA $NNNN,Y
        case 0x1d: instructionNotImplementedError(state); break;    // ORA $NNNN,X
        case 0x1e: instructionNotImplementedError(state); break;    // ASL $NNNN,X
        case 0x20: instructionNotImplementedError(state); break;    // JSR $NNNN
        case 0x21: instructionNotImplementedError(state); break;    // AND ($NN,X)
        case 0x24: instructionNotImplementedError(state); break;    // BIT $NN
        case 0x25: instructionNotImplementedError(state); break;    // AND $NN
        case 0x26: instructionNotImplementedError(state); break;    // ROL $NN
        case 0x28: instructionNotImplementedError(state); break;    // PLP
        case 0x29: instructionNotImplementedError(state); break;    // #$NN
        case 0x2a: instructionNotImplementedError(state); break;    // ROL A
        case 0x2c: instructionNotImplementedError(state); break;    // BIT $NNNN
        case 0x2d: instructionNotImplementedError(state); break;    // AND $NNNN
        case 0x2e: instructionNotImplementedError(state); break;    // ROL $NNNN
        case 0x30: instructionNotImplementedError(state); break;    // BMI $NN
        case 0x31: instructionNotImplementedError(state); break;    // AND ($NN),Y
        case 0x35: instructionNotImplementedError(state); break;    // AND $NN,X
        case 0x36: instructionNotImplementedError(state); break;    // ROL $NN,X
        case 0x38: instructionNotImplementedError(state); break;    // SEC
        case 0x39: instructionNotImplementedError(state); break;    // AND $NNNN,Y
        case 0x3d: instructionNotImplementedError(state); break;    // AND $NNNN,X
        case 0x3e: instructionNotImplementedError(state); break;    // ROL $NNNN,X
        case 0x40: instructionNotImplementedError(state); break;    // RSI
        case 0x41: instructionNotImplementedError(state); break;    // EOR ($NN,X)
        case 0x45: instructionNotImplementedError(state); break;    // EOR $NN
        case 0x46: instructionNotImplementedError(state); break;    // LSR $NN
        case 0x48: instructionNotImplementedError(state); break;    // PHA
        case 0x49: instructionNotImplementedError(state); break;    // EOR #$NN
        case 0x4a: instructionNotImplementedError(state); break;    // LSR A
        case 0x4c: instructionNotImplementedError(state); break;    // JMP $NNNN
        case 0x4d: instructionNotImplementedError(state); break;    // EOR $NNNN
        case 0x4e: instructionNotImplementedError(state); break;    // LSR $NNNN
        case 0x50: instructionNotImplementedError(state); break;    // BVC $NN
        case 0x51: instructionNotImplementedError(state); break;    // EOR ($NN),Y
        case 0x55: instructionNotImplementedError(state); break;    // EOR $NN,X
        case 0x56: instructionNotImplementedError(state); break;    // LSR $NN,X
        case 0x58: instructionNotImplementedError(state); break;    // CLI
        case 0x59: instructionNotImplementedError(state); break;    // EOR $NNNN,Y
        case 0x5d: instructionNotImplementedError(state); break;    // EOR $NNNN,X
        case 0x5e: instructionNotImplementedError(state); break;    // LSR $NNNN,X
        case 0x60: instructionNotImplementedError(state); break;    // RTS
        case 0x61: instructionNotImplementedError(state); break;    // ADC ($NN,X)
        case 0x65: instructionNotImplementedError(state); break;    // ADC $NN
        case 0x66: instructionNotImplementedError(state); break;    // ROR $NN
        case 0x68: instructionNotImplementedError(state); break;    // PLA
        case 0x69: instructionNotImplementedError(state); break;    // ADC #$NN
        case 0x6a: instructionNotImplementedError(state); break;    // ROR A
        case 0x6c: instructionNotImplementedError(state); break;    // JMP $NN
        case 0x6d: instructionNotImplementedError(state); break;    // ADC $NNNN
        case 0x6e: instructionNotImplementedError(state); break;    // ROR $NNNN,X
        case 0x70: instructionNotImplementedError(state); break;    // BVS $NN
        case 0x71: instructionNotImplementedError(state); break;    // ADC ($NN),Y
        case 0x75: instructionNotImplementedError(state); break;    // ADC $NN,X
        case 0x76: instructionNotImplementedError(state); break;    // ROR $NN,X
        case 0x78: instructionNotImplementedError(state); break;    // SEI
        case 0x79: instructionNotImplementedError(state); break;    // ADC $NNNN,Y
        case 0x7d: instructionNotImplementedError(state); break;    // ADC $NNNN,X
        case 0x7e: instructionNotImplementedError(state); break;    // ROR $NNNN
        case 0x81: instructionNotImplementedError(state); break;    // STA ($NN,X)
        case 0x84: instructionNotImplementedError(state); break;    // STY $NN
        case 0x85: instructionNotImplementedError(state); break;    // STA $NN
        case 0x86: instructionNotImplementedError(state); break;    // STX $NN
        case 0x88: instructionNotImplementedError(state); break;    // DEY
        case 0x8a: instructionNotImplementedError(state); break;    // TXA
        case 0x8c: instructionNotImplementedError(state); break;    // STY $NNNN
        case 0x8d: instructionNotImplementedError(state); break;    // STA $NNNN
        case 0x8e: instructionNotImplementedError(state); break;    // STX $NNNN
        case 0x90: instructionNotImplementedError(state); break;    // BCC $NN
        case 0x91: instructionNotImplementedError(state); break;    // STA ($NN),Y
        case 0x94: instructionNotImplementedError(state); break;    // STY $NN,X
        case 0x95: instructionNotImplementedError(state); break;    // STA $NN,X
        case 0x96: instructionNotImplementedError(state); break;    // STX $NN,Y
        case 0x98: instructionNotImplementedError(state); break;    // TYA
        case 0x99: instructionNotImplementedError(state); break;    // STA $NNNN,Y
        case 0x9a: instructionNotImplementedError(state); break;    // TXS
        case 0x9d: instructionNotImplementedError(state); break;    // STA $NNNN,X
        case 0xa0: instructionNotImplementedError(state); break;    // LDY #$NN
        case 0xa1: instructionNotImplementedError(state); break;    // LDA ($NN,X)
        case 0xa2: instructionNotImplementedError(state); break;    // LDX #$NN
        case 0xa4: instructionNotImplementedError(state); break;    // LDY $NN
        case 0xa5: instructionNotImplementedError(state); break;    // LDA $NN
        case 0xa6: instructionNotImplementedError(state); break;    // LDX $NN
        case 0xa8: instructionNotImplementedError(state); break;    // TAY
        case 0xa9: instructionNotImplementedError(state); break;    // LDA #$NN
        case 0xaa: instructionNotImplementedError(state); break;    // TAX
        case 0xac: instructionNotImplementedError(state); break;    // LDY $NNNN
        case 0xad: instructionNotImplementedError(state); break;    // LDA $NNNN
        case 0xae: instructionNotImplementedError(state); break;    // LDX $NNNN
        case 0xb0: instructionNotImplementedError(state); break;    // BCS $NN
        case 0xb1: instructionNotImplementedError(state); break;    // LDA ($NN),Y
        case 0xb4: instructionNotImplementedError(state); break;    // LDY $NN,X
        case 0xb5: instructionNotImplementedError(state); break;    // LDA $NN,X
        case 0xb6: instructionNotImplementedError(state); break;    // LDX $NN,Y
        case 0xb8: instructionNotImplementedError(state); break;    // CLV
        case 0xb9: instructionNotImplementedError(state); break;    // LDA $NNNN,Y
        case 0xba: instructionNotImplementedError(state); break;    // TSX
        case 0xbc: instructionNotImplementedError(state); break;    // LDY $NNNN,X
        case 0xbd: instructionNotImplementedError(state); break;    // LDA $NNNN,X
        case 0xbe: instructionNotImplementedError(state); break;    // LDX $NNNN,Y
        case 0xc0: instructionNotImplementedError(state); break;    // CPY #$NN
        case 0xc1: instructionNotImplementedError(state); break;    // CMP ($NN,X)
        case 0xc4: instructionNotImplementedError(state); break;    // CPY $NN
        case 0xc5: instructionNotImplementedError(state); break;    // CMP $NN
        case 0xc6: instructionNotImplementedError(state); break;    // DEC $NN
        case 0xc8: instructionNotImplementedError(state); break;    // INY
        case 0xc9: instructionNotImplementedError(state); break;    // CMP #$NN
        case 0xca: instructionNotImplementedError(state); break;    // DEX
        case 0xcc: instructionNotImplementedError(state); break;    // CPY $NNNN
        case 0xcd: instructionNotImplementedError(state); break;    // CMP $NNNN
        case 0xce: instructionNotImplementedError(state); break;    // DEC $NNNN
        case 0xd0: instructionNotImplementedError(state); break;    // BNE $NN
        case 0xd1: instructionNotImplementedError(state); break;    // CMP ($NN),Y
        case 0xd5: instructionNotImplementedError(state); break;    // CMP $NN,X
        case 0xd6: instructionNotImplementedError(state); break;    // DEC $NN,X
        case 0xd8: instructionNotImplementedError(state); break;    // CLD
        case 0xd9: instructionNotImplementedError(state); break;    // CMP $NNNN,Y
        case 0xdd: instructionNotImplementedError(state); break;    // CMP $NNNN,X
        case 0xde: instructionNotImplementedError(state); break;    // DEC $NNNN,X
        case 0xe0: instructionNotImplementedError(state); break;    // CPX #$NN
        case 0xe1: instructionNotImplementedError(state); break;    // SBC ($NN,X)
        case 0xe4: instructionNotImplementedError(state); break;    // CPX $NN
        case 0xe5: instructionNotImplementedError(state); break;    // SBC $NN
        case 0xe6: instructionNotImplementedError(state); break;    // INC $NN
        case 0xe8: instructionNotImplementedError(state); break;    // INX
        case 0xe9: instructionNotImplementedError(state); break;    // SBC #$NN
        case 0xea: instructionNotImplementedError(state); break;    // NOP
        case 0xec: instructionNotImplementedError(state); break;    // CPX $NNNN
        case 0xed: instructionNotImplementedError(state); break;    // SBC $NNNN
        case 0xee: instructionNotImplementedError(state); break;    // INC $NNNN
        case 0xf0: instructionNotImplementedError(state); break;    // BEQ $NN
        case 0xf1: instructionNotImplementedError(state); break;    // SBC ($NN),Y
        case 0xf5: instructionNotImplementedError(state); break;    // SBC $NN,X
        case 0xf6: instructionNotImplementedError(state); break;    // INC $NN,X
        case 0xf8: instructionNotImplementedError(state); break;    // SED
        case 0xf9: instructionNotImplementedError(state); break;    // SBC $NNNN,Y
        case 0xfd: instructionNotImplementedError(state); break;    // SBC $NNNN,X
        case 0xfe: instructionNotImplementedError(state); break;    // INC $NNNN,X
        default: unknownOpcodeError(state); break;
    }

    state->pc += 1;
}

void instructionNotImplementedError(State2A03* state) {
    printf("ERROR: Instruction not implemented\n");
}

void unknownOpcodeError(State2A03* state) {
    printf("ERROR: Unknown opcode\n");
}