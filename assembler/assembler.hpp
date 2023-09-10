#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <list>
#include <map>

#include "../program/program.hpp"
#include "../utils/string.hpp"
#include "../enums/instructions.hpp"


class Assembler
{
public:
    

    Assembler(const std::string filePath) : filePath(filePath) { 
        jumpInstructions[0] = JZ; 
        jumpInstructions[1] = JMP;
        jumpInstructions[2] = CALL;
    }


    Program assemble();
    bool isJump(Instruction instruction);
    Instruction translate(std::string operation);
    std::string codeToMnemonic(Instruction code);
    

private:
    std::string instructionMnemonics[INSTRUCTIONS_COUNT] = {
        "push","sub","jz","jmp","hlt","pops","restore","add","call","ret","dup","mul", "nop", "pop"
    };
    const std::string filePath;
    Instruction jumpInstructions[JUMP_INSTRUCTIONS_COUNT];
};