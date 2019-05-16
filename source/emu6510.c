#include <stdio.h>
#include <stdlib.h>
#include "disassembler.h"

#include "emu6510.h"

#define DEBUG

void emulate6510(State6510* state) {
    #ifdef DEBUG
    disassemble6502(state->memory, state->pc);
    #endif

    unsigned char* opcode = &state->memory[state->pc]; state->pc++;

    switch (*opcode) {
        case 0x00:      // BRK
            {
                uint16_t returnAddress = state->pc + 2;
                state->p.i = 1;
                state->p.b = 1;
                state->memory[state->s] = returnAddress & 0xff;
                state->memory[state->s+1] = returnAddress >> 8;
                state->s -= 2;
                uint8_t stateByte = 0b00000000;
                stateByte |= state->p.c << 6;
                stateByte |= state->p.z << 5;
                stateByte |= state->p.i << 4;
                stateByte |= state->p.d << 3;
                stateByte |= state->p.b << 2;
                stateByte |= state->p.v << 1;
                stateByte |= state->p.n;
                state->memory[state->s] = stateByte; state->s--;
                state->pc = (state->memory[0xffff]<<8) | state->memory[0xfffe];
            }
            break;
        case 0x01:      // ORA ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break; 
        case 0x05:      // ORA $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break; 
        case 0x06:      // ASL $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint16_t answer = state->memory[address] << 1;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x08:      // PHP
            {
                uint8_t stateByte = 0b00000000;
                stateByte |= state->p.c << 6;
                stateByte |= state->p.z << 5;
                stateByte |= state->p.i << 4;
                stateByte |= state->p.d << 3;
                stateByte |= state->p.b << 2;
                stateByte |= state->p.v << 1;
                stateByte |= state->p.n;
                state->memory[state->s] = stateByte; state->s--;
            }
            break;
        case 0x09:      // ORA #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                uint8_t answer = state->a | operand;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x0a:      // ASL A
            {
                uint16_t answer = state->a << 2;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x0d:      // ORA $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break; 
        case 0x0e:      // ASL $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint16_t answer = state->memory[address] << 2;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x10:      // BPL $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.n == 0) state->pc += targetOffset;
            }
            break;
        case 0x11:      // ORA ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break; 
        case 0x15:      // ORA $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x16:      // ASL $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint16_t answer = state->memory[address] << 2;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x18:      // CLC
            {
                state->p.c = 0;
            }
            break;
        case 0x19:      // ORA $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x1d:      // ORA $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->a | state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x1e:      // ASL $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint16_t answer = state->memory[address] << 2;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x20:      // JSR $NNNN
            {
                uint16_t jumpAddress = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint16_t returnAddress = state->pc - 1;
                state->memory[state->s] = returnAddress & 0xff;
                state->memory[state->s+1] = returnAddress >> 8;
                state->s -= 2;
                state->pc = jumpAddress;
            }
            break;
        case 0x21:      // AND ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x24:      // BIT $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->p.z = ((state->a & state->memory[address]) == 0);
                state->p.v = (state->memory[address] & 0b01000000) >> 6;
                state->p.n = (state->memory[address] & 0b10000000) >> 7;
            }
            break;
        case 0x25:      // AND $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x26:      // ROL $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = ((state->memory[address] << 1) & 0b11111110) | state->p.c;
                state->p.c = (state->memory[address] & 0b10000000) >> 7;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x28:      // PLP
            {
                state->s--; uint8_t stateByte = state->memory[state->s];
                state->p.c = (stateByte & 0b01000000) >> 6;
                state->p.z = (stateByte & 0b00100000) >> 5;
                state->p.i = (stateByte & 0b00010000) >> 4;
                state->p.d = (stateByte & 0b00001000) >> 3;
                state->p.b = (stateByte & 0b00000100) >> 2;
                state->p.v = (stateByte & 0b00000010) >> 1;
                state->p.n = stateByte & 0b00000001;
            }
            break;
        case 0x29:      // AND #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                uint8_t answer = state->a & operand;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x2a:      // ROL A
            {
                uint8_t answer = ((state->a << 1) & 0b11111110) | state->p.c;
                state->p.c = (state->a & 0b10000000) >> 7;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x2c:      // BIT $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->p.z = ((state->a & state->memory[address]) == 0);
                state->p.v = (state->memory[address] & 0b01000000) >> 6;
                state->p.n = (state->memory[address] & 0b10000000) >> 7;
            }
            break;
        case 0x2d:      // AND $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x2e:      // ROL $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = ((state->memory[address] << 1) & 0b11111110) | state->p.c;
                state->p.c = (state->memory[address] & 0b10000000) >> 7;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x30:      // BMI $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.n == 1) state->pc += targetOffset;
            }
            break;
        case 0x31:      // AND ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x35:      // AND $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x36:      // ROL $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = ((state->memory[address] << 1) & 0b11111110) | state->p.c;
                state->p.c = (state->memory[address] & 0b10000000) >> 7;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x38:      // SEC
            {
                state->p.c = 1;
            }
            break;
        case 0x39:      // AND $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x3d:      // AND $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->a & state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x3e:      // ROL $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = ((state->memory[address] << 1) & 0b11111110) | state->p.c;
                state->p.c = (state->memory[address] & 0b10000000) >> 7;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x40:      // RTI
            {
                state->s++; uint8_t stateByte = state->memory[state->s];
                state->p.c = (stateByte & 0b01000000) >> 6;
                state->p.z = (stateByte & 0b00100000) >> 5;
                state->p.i = (stateByte & 0b00010000) >> 4;
                state->p.d = (stateByte & 0b00001000) >> 3;
                state->p.b = (stateByte & 0b00000100) >> 2;
                state->p.v = (stateByte & 0b00000010) >> 1;
                state->p.n = stateByte & 0b00000001;
                state->s += 2; state->pc = (state->memory[state->s+1]<<8) | state->memory[state->s];
            }
            break;
        case 0x41:      // EOR ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x45:      // EOR $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x46:      // LSR $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->memory[address] >> 1;
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x48:      // PHA
            {
                state->memory[state->s] = state->a; state->s--;
            }
            break;
        case 0x49:      // EOR #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                uint8_t answer = state->a ^ operand;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x4a:      // LSR A
            {
                uint8_t answer = state->a >> 1;
                state->p.c = state->a & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x4c: instructionNotImplementedError(state); state->pc += 2; break;    // JMP $NNNN
        case 0x4d:      // EOR $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x4e:      // LSR $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address] >> 1;
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x50:      // BVC $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.v == 0) state->pc += targetOffset;
            }
            break;
        case 0x51:      // EOR ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x55:      // EOR $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x56:      // LSR $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address] >> 1;
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x58:      // CLI
            {
                state->p.i = 0;
            }
            break;
        case 0x59:      // EOR $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x5d:      // EOR $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->a ^ state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x5e:      // LSR $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->memory[address] >> 1;
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x60:      // RTS
            {
                state->s -= 2; state->pc = ((state->memory[state->s+1]<<8) | state->memory[state->s]) - 1;
            }
            break;
        case 0x61:      // ADC ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x65:      // ADC $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x66:      // ROR $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = (state->memory[address]>>1) | (state->p.c<<7);
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x68:      // PLA
            {
                state->s--; uint8_t answer = state->memory[state->s];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x69:      // ADC #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                uint16_t answer = state->a + operand + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - operand);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x6a:      // ROR A
            {
                uint8_t answer = (state->a>>1) | (state->p.c<<7);
                state->p.c = state->a & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x6c: instructionNotImplementedError(state); state->pc++; break;    // JMP $NN
        case 0x6d:      // ADC $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x6e:      // ROR $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = (state->memory[address]>>1) | (state->p.c<<7);
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x70:      // BVS $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.v == 1) state->pc += targetOffset;
            }
            break;
        case 0x71:      // ADC ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x75:      // ADC $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x76:      // ROR $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = (state->memory[address]>>1) | (state->p.c<<7);
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x78:      // SEI
            {
                state->p.i = 1;
            }
            break;
        case 0x79:      // ADC $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x7d:      // ADC $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint16_t answer = state->a + state->memory[address] + state->p.c;
                state->p.c = (answer > 0xff);
                state->p.z = (answer == 0);
                state->p.v = (state->a > 127 - state->memory[address]);     // FIXIT not quite sure if that is correct
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x7e:      // ROR $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = (state->memory[address]>>1) | (state->p.c<<7);
                state->p.c = state->memory[address] & 0b00000001;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0x81:      // STA ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                state->memory[address] = state->a;
            }
            break;
        case 0x84:      // STY $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->memory[address] = state->y;
            }
            break;
        case 0x85:      // STA $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->memory[address] = state->a;
            }
            break;
        case 0x86:      // STX $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->memory[address] = state->x;
            }
            break;
        case 0x88:      // DEY
            {
                uint8_t answer = state->y - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->y = answer;
            }
            break;
        case 0x8a:      // TXA
            {
                uint8_t answer = state->x;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x8c:      // STY $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->memory[address] = state->y;
            }
            break;
        case 0x8d:      // STA $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->memory[address] = state->a;
            }
            break;
        case 0x8e:      // STX $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->memory[address] = state->x;
            }
            break;
        case 0x90:      // BCC $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.c == 0) state->pc += targetOffset;
            }
            break;
        case 0x91:      // STA ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                state->memory[address] = state->a;
            }
            break;
        case 0x94:      // STY $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                state->memory[address] = state->y;
            }
            break;
        case 0x95:      // STA $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                state->memory[address] = state->a;
            }
            break;
        case 0x96:      // STX $NN,Y
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->y;
                state->memory[address] = state->x;
            }
            break;
        case 0x98:      // TYA
            {
                uint8_t answer = state->y;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0x99:      // STA $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                state->memory[address] = state->a;
            }
            break;
        case 0x9a:      // TXS
            {
                state->s = state->x;
            }
            break;
        case 0x9d:      // STA $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                state->memory[address] = state->a;
            }
            break;
        case 0xa0:      // LDY #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.z = (operand == 0);
                state->p.n = (operand & 0b10000000) >> 7;
                state->y = operand;
            }
            break;
        case 0xa1:      // LDA ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xa2:      // LDX #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.z = (operand == 0);
                state->p.n = (operand & 0b10000000) >> 7;
                state->x = operand;
            }
            break;
        case 0xa4:      // LDY $NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.z = (operand == 0);
                state->p.n = (operand & 0b10000000) >> 7;
                state->y = operand;
            }
            break;
        case 0xa5:      // LDA $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xa6:      // LDX $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xa8:      // TAY
            {
                uint8_t answer = state->a;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->y = answer;
            }
            break;
        case 0xa9:      // LDA #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.z = (operand == 0);
                state->p.n = (operand & 0b10000000) >> 7;
                state->a = operand;
            }
            break;
        case 0xaa:      // TAX
            {
                uint8_t answer = state->a;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xac:      // LDY $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xad:      // LDA $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xae:      // LDX $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xb0:      // BCS $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.c == 1) state->pc += targetOffset;
            }
            break;
        case 0xb1:      // LDA ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xb4:      // LDY $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->y = answer;
            }
            break;
        case 0xb5:      // LDA $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xb6:      // LDX $NN,Y
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->y;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xb8:      // CLV
            {
                state->p.v = 0;
            }
            break;
        case 0xb9:      // LDA $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xba:      // TSX
            {
                uint8_t answer = state->s;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xbc:      // LDY $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->y = answer;
            }
            break;
        case 0xbd:      // LDA $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->a = answer;
            }
            break;
        case 0xbe:      // LDX $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->memory[address];
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xc0:      // CPY #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.c = (state->y >= operand);
                state->p.z = (state->y == operand);
                state->p.n = (state->y < operand);
            }
            break;
        case 0xc1:      // CMP ($NN,X)
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xc4:      // CPY $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->p.c = (state->y >= state->memory[address]);
                state->p.z = (state->y == state->memory[address]);
                state->p.n = (state->y < state->memory[address]);
            }
            break;
        case 0xc5:      // CMP $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xc6:      // DEC $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->memory[address] - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xc8:      // INY
            {
                uint8_t answer = state->y + 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->y = answer;
            }
            break;
        case 0xc9:      // CMP #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.c = (state->a >= operand);
                state->p.z = (state->a == operand);
                state->p.n = (state->a < operand);
            }
            break;
        case 0xca:      // DEX
            {
                uint8_t answer = state->x - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xcc:      // CPY $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->p.c = (state->y >= state->memory[address]);
                state->p.z = (state->y == state->memory[address]);
                state->p.n = (state->y < state->memory[address]);
            }
            break;
        case 0xcd:      // CMP $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xce:      // DEC $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address] - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xd0:      // BNE $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.z == 0) state->pc += targetOffset;
            }
            break;
        case 0xd1:      // CMP ($NN),Y
            {
                uint8_t addressloc = opcode[1]; state->pc++;
                uint16_t address = (state->memory[addressloc+1]<<8) | state->memory[addressloc];
                address += state->y;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xd5:      // CMP $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xd6:      // DEC $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address] - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xd8:      // CLD
            {
                state->p.d = 0;
            }
            break;
        case 0xd9:      // CMP $NNNN,Y
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xdd:      // CMP $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                state->p.c = (state->a >= state->memory[address]);
                state->p.z = (state->a == state->memory[address]);
                state->p.n = (state->a < state->memory[address]);
            }
            break;
        case 0xde:      // DEC $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->y;
                uint8_t answer = state->memory[address] - 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xe0:      // CPX #$NN
            {
                uint8_t operand = opcode[1]; state->pc++;
                state->p.c = (state->x >= operand);
                state->p.z = (state->x == operand);
                state->p.n = (state->x < operand);
            }
            break;
        case 0xe1: instructionNotImplementedError(state); state->pc++; break;    // SBC ($NN,X)
        case 0xe4:      // CPX $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                state->p.c = (state->x >= state->memory[address]);
                state->p.z = (state->x == state->memory[address]);
                state->p.n = (state->x < state->memory[address]);
            }
            break;
        case 0xe5: instructionNotImplementedError(state); state->pc++; break;    // SBC $NN
        case 0xe6:      // INC $NN
            {
                uint8_t address = opcode[1]; state->pc++;
                uint8_t answer = state->memory[address] + 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xe8:      // INX
            {
                uint8_t answer = state->x + 1;
                state->p.z = (answer == 0);
                state->p.n = (answer & 0b10000000) >> 7;
                state->x = answer;
            }
            break;
        case 0xe9: instructionNotImplementedError(state); state->pc++; break;    // SBC #$NN
        case 0xea:      // NOP
            break;
        case 0xec:      // CPX $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                state->p.c = (state->x >= state->memory[address]);
                state->p.z = (state->x == state->memory[address]);
                state->p.n = (state->x < state->memory[address]);
            }
            break;
        case 0xed: instructionNotImplementedError(state); state->pc += 2; break;    // SBC $NNNN
        case 0xee:      // INC $NNNN
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                uint8_t answer = state->memory[address] + 1;
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xf0:      // BEQ $NN
            {
                uint8_t targetOffset = opcode[1]; state->pc++;
                if (state->p.z == 1) state->pc += targetOffset;
            }
            break;
        case 0xf1: instructionNotImplementedError(state); state->pc++; break;    // SBC ($NN),Y
        case 0xf5: instructionNotImplementedError(state); state->pc++; break;    // SBC $NN,X
        case 0xf6:      // INC $NN,X
            {
                uint8_t address = opcode[1]; state->pc++;
                address += state->x;
                uint8_t answer = state->memory[address] + 1;
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        case 0xf8:      // SED
            {
                state->p.d = 1;
            }
            break;
        case 0xf9: instructionNotImplementedError(state); state->pc += 2; break;    // SBC $NNNN,Y
        case 0xfd: instructionNotImplementedError(state); state->pc += 2; break;    // SBC $NNNN,X
        case 0xfe:      // INC $NNNN,X
            {
                uint16_t address = (opcode[2]<<8) | opcode[1]; state->pc += 2;
                address += state->x;
                uint8_t answer = state->memory[address] + 1;
                state->p.n = (answer & 0b10000000) >> 7;
                state->memory[address] = answer;
            }
            break;
        default: unknownOpcodeError(state); break;
    }
}

void instructionNotImplementedError(State6510* state) {
    printf("ERROR: Instruction not implemented\n");
    exit(1);
}

void unknownOpcodeError(State6510* state) {
    printf("ERROR: Unknown opcode\n");
    exit(1);
}

State6510* makeState6510Default() {
    State6510* state = (State6510*) malloc(sizeof(State6510));

    state->memory = (uint8_t*) malloc(64000);
    state->memory[0xfffa] = 0x43; state->memory[0xfffb] = 0xfe;     // NMI
    state->memory[0xfffc] = 0xe2; state->memory[0xfffd] = 0xfc;     // Reset
    state->memory[0xfffe] = 0x48; state->memory[0xffff] = 0xff;     // IRQ/BRK
    
    state->s = 0x01ff;

    return state;
}

void printState6510(State6510* state) {
    printf("\n");

    printf("############### State6510 ###############\n");
    printf("a:    $%02x\n", state->a);
    printf("x:    $%02x\n", state->x);
    printf("y:    $%02x\n", state->y);
    printf("pc:   $%04x\n", state->pc);
    printf("s:    $%04x\n", state->s);
    printf("#########################################\n");

    printf("\n");
}