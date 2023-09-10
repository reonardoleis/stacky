#pragma once

#include "../stack/stack.hpp"
#include "../program/program.hpp"
#include "../enums/instructions.hpp"
#include "../pair/pair.hpp"
#include "../value/value.hpp"
#include <iostream>

class Machine
{
public:
    Machine(Program program) : pc(0), program(program), stack(Stack()), popStack(Stack()), callStack(Stack()) {}
    void step();
    void run();
    void run(bool debug);
    Value arithmeticOperation(Instruction operation, Value op1, Value op2);
    void printState();
    std::string getOutput();
private:
    int pc;
    Program program;
    Stack stack;
    Stack popStack;
    Stack callStack;
};