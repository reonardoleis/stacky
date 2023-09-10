#pragma once

#include <string>
#include <tuple>
#include <iostream>
#include "../value/value.hpp"

std::string trimLeftRight(std::string str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    return str.substr(first, (last - first + 1));
}

std::string sanitize(std::string str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    size_t i = 0;
    while (i < str.size())
    {
        if (isalnum(str[i]) || str[i] == '_')
        {
            i++;
        }
        else
        {
            str.erase(i, 1);
        }
    }

    
    return str.substr(first, (last - first + 1));
}


std::tuple<std::string, std::string> splitInstruction(std::string instruction, const std::string delimiter = std::string(" "))
{
    size_t pos = 0;
    std::string token;

    std::tuple<std::string, std::string> tuple;
    instruction = trimLeftRight(instruction);
    pos = instruction.find(delimiter);
    if (pos != std::string::npos)
    {
        std::string operation = instruction.substr(0, pos);
        std::string operand = instruction.substr(pos + 1, instruction.size());

        tuple = std::tuple<std::string, std::string>(sanitize(operation), sanitize(operand));
    }
    else
    {
        tuple = std::tuple<std::string, std::string>(sanitize(instruction), std::string(""));
    }

    return tuple;
}

std::string removeExtension(std::string filePath)
{
    size_t lastindex = filePath.find_last_of(".");
    return filePath.substr(0, lastindex);
}