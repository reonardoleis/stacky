#include "program.hpp"
#include <iterator>

std::tuple<int, Value> Program::at(int pc)
{
    auto element = code.begin();
    std::advance(element, pc);
    return *element;
}

Instruction Program::operationAt(int pc)
{
    std::tuple<int, Value> instruction = at(pc);
    return Instruction(std::get<0>(instruction));
}

Value Program::operandAt(int pc)
{
    std::tuple<int, Value> instruction = at(pc);
    return std::get<1>(instruction);
}

int Program::addressOfLabel(std::string label)
{
    return labels.at(label);
}

void Program::setLabelAddress(std::string label, int address)
{
    labels.insert(std::pair<std::string, int>(label, address));
}

int Program::programSize()
{
    return code.size();
}

void Program::save(std::string filePath)
{
    std::ofstream file(filePath);
    for (auto instruction : code)
    {
        if (std::get<1>(instruction).type != Value::None) 
            file << std::get<0>(instruction) << "," << std::get<1>(instruction).getStringValue() << std::endl;
        else
            file << std::get<0>(instruction) << std::endl;
    }

    file.close();
}

void Program::load(std::string filePath)
{
    std::list<std::tuple<int, Value>> code = std::list<std::tuple<int, Value>>();

    std::string line = std::string("");

    std::fstream file(filePath);
    while (std::getline(file, line))
    {
        std::tuple<std::string, std::string> instruction = splitInstruction(line, std::string(","));
        std::string operation = std::get<0>(instruction);
        std::string operand = std::get<1>(instruction);
        Value operandValue = operand;
        if (atoi(operand.c_str()) != 0) {
            operandValue = Value(atoi(operand.c_str()));
        }

        code.push_back(std::tuple<int, Value>(atoi(operation.c_str()), operandValue));
    }

    this->code = code;
}