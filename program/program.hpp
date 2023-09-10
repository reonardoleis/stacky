#pragma once

#include <tuple>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include "../enums/instructions.hpp"
#include "../value/value.hpp"
#include "../utils/string.hpp"
#include <string.h>

class Program
{
public:
    Program() : code(std::list<std::tuple<int, Value>>()) {}
    Program(std::list<std::tuple<int, Value>> programCode) : code(programCode) {}
    std::tuple<int, Value> at(int pc);
    Instruction operationAt(int pc);
    Value operandAt(int pc);
    int addressOfLabel(std::string label);
    void setLabelAddress(std::string label, int address);
    int programSize();
    void save(std::string filePath);
    void load(std::string filePath);

private:
    std::list<std::tuple<int, Value>> code;
    std::map<std::string, int> labels;
};