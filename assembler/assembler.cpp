#include "assembler.hpp"
#include <iostream>
#include <string.h>
bool isLabel(const std::string line)
{
    return line.find(std::string(":"), 0) != std::string::npos;
}

Instruction Assembler::translate(std::string operation)
{
    int i;
    for (i = 0; i < INSTRUCTIONS_COUNT; i++)
    {
        if (strcmp(operation.c_str(), instructionMnemonics[i].c_str()) == 0)
            return Instruction(i);
    }

    return NOP;
}

bool Assembler::isJump(Instruction instruction)
{
    int i;
    for (i = 0; i < JUMP_INSTRUCTIONS_COUNT; i++)
    {
        if (instruction == jumpInstructions[i])
            return true;
    }

    return false;
}

Program Assembler::assemble()
{
    std::list<std::tuple<int, Value>> instructions;
    std::map<std::string, int> labels;

    std::string line = std::string("");

    std::ifstream file1(filePath);
    int instructionNumber = 0;
    while (std::getline(file1, line))
    {
        if (line.size() == 0) continue;
        if (isLabel(line))
        {
            labels.insert(std::pair<std::string, int>(line.substr(0, line.size() - 1), instructionNumber));
        }
        else
        {
            instructionNumber++;
        }
    }

    std::ifstream file2(filePath);
    while (std::getline(file2, line))
    {
        if (line.size() == 0) continue;
        if (isLabel(line))
            continue;

        std::tuple<std::string, std::string> instruction = splitInstruction(line);
        std::string operationMnemonic = std::get<0>(instruction);
        std::string operandText = std::get<1>(instruction);

        Instruction operation = translate(operationMnemonic);
        Value operand;

        if (atoi(operandText.c_str()) != 0)
        {
            operand = Value(atoi(operandText.c_str()));
        }
        else
        {
            operand = Value(operandText);
            if (operandText.size() == 0)
                operand = Value();
        }

        if (isJump(operation))
        {
            operand = Value(labels.at(operand.stringValue));
        }

        instructions.push_back(std::tuple<int, Value>(int(operation), operand));
    }

    return Program(instructions);
}

std::string Assembler::codeToMnemonic(Instruction code)
{

    int i;
    for (i = 0; i < INSTRUCTIONS_COUNT; i++)
    {
        if (code == Instruction(i))
            return instructionMnemonics[i];
    }

    return "nop";
}