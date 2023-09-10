#include "machine.hpp"

Value Machine::arithmeticOperation(Instruction operation, Value op1, Value op2)
{
    if (operation == SUB)
    {
        return op2 - op1;
    }

    switch (operation)
    {
    case ADD:
        return op1 + op2;
    case MUL:
        return op1 * op2;
    }

    return Value();
}

void Machine::step()
{
    Instruction operation = program.operationAt(pc);
    Value operand = program.operandAt(pc);

    switch (operation)
    {
    case PUSH:
    {
        stack.push(operand);
        break;
    }

    case SUB:
    case MUL:
    case ADD:
    {
        Pair pair = stack.pop2();
        stack.push(arithmeticOperation(operation, pair.first(), pair.second()));
        break;
    }

    case JZ:
    {
        Value stackTop = stack.pop();
        if (stackTop.type == Value::Int && stackTop.intValue == 0)
        {
            pc = operand.intValue - 1;
        }

        stack.push(stackTop);
        break;
    }

    case JMP:
    {
        pc = (operand).intValue - 1;
        break;
    }

    case HLT:
    {
        pc = program.programSize() + 1;
        break;
    }

    case POPS:
    {
        Value stackTop = stack.pop();
        popStack.push(stackTop);
        break;
    }

    case RESTORE:
    {
        Value popStackTop = popStack.pop();
        stack.push(popStackTop);
        break;
    }

    case CALL:
    {
        callStack.push(Value(pc));
        pc = operand.intValue - 1;
        break;
    }

    case RET:
    {
        Value callStackTop = callStack.pop();
        pc = callStackTop.intValue;
        break;
    }

    case DUP:
    {
        Value stackTop = stack.pop();
        stack.push(stackTop);
        stack.push(stackTop);
        break;
    }

    case POP:
    {
        stack.pop();
        break;
    }

    case DIV:
    {
        Pair pair = stack.pop2();
        stack.push(pair.second() / pair.first());
        break;
    }
    }

    pc++;
}

void Machine::run()
{
    while (pc < program.programSize())
    {
        step();
    }
}

void Machine::run(bool debug)
{
    while (pc < program.programSize())
    {
        
        if (debug)
        {
            printState();
            std::string input;
            std::cin >> input;
        }
        step();

    }
}

void Machine::printState()
{
    std::cout << "PC: " << pc << " | ";
    std::string instructionMnemonics[INSTRUCTIONS_COUNT] = {
        "push","sub","jz","jmp","hlt","pops","restore","add","call","ret","dup","mul", "nop"
    };
    std::cout << "Instruction: " << instructionMnemonics[program.operationAt(pc)] << " | ";
    std::cout << "Stack: " << stack.toString() << " | ";
    std::cout << "Pop Stack: " << popStack.toString() << " | ";
    std::cout << "Call Stack: " << callStack.toString() << std::endl;
}

std::string Machine::getOutput()
{
    return stack.pop().getStringValue();
}