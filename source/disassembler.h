#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

int disassemble6502(unsigned char* codebuffer, int pc);
void unknownOpcode(unsigned char* code);

#endif