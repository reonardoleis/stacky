#pragma once

#define INSTRUCTIONS_COUNT 14
#define JUMP_INSTRUCTIONS_COUNT 3

enum Instruction { 
        PUSH, SUB, JZ, JMP, HLT,
        POPS, RESTORE, ADD, CALL,
        RET, DUP, MUL, NOP, POP
};