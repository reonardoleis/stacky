#include <iostream>
#include <string>

#include "value/value.cpp"
#include "pair/pair.cpp"
#include "stack/stack.cpp"
#include "program/program.cpp"
#include "utils/string.hpp"
#include "assembler/assembler.cpp"
#include "machine/machine.cpp"

#include <tuple>
#include <list>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <assemble|run|rund> <input file>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string inputFile = argv[2];

    if (command != "assemble" && command != "run" && command != "rund")
    {
        std::cout << "Usage: " << argv[0] << " <assemble|run|rund> <input file>" << std::endl;
        return 1;
    }

    if (command == "assemble")
    {
        Assembler assembler(inputFile);
        Program program = assembler.assemble();
        program.save(removeExtension(inputFile) + "_out.bin");
        return 0;
    }

    if (command == "run" || command == "rund")
    {
        Program program = Program();
        program.load(inputFile);
        Machine machine = Machine(program);
        machine.run(command == "rund");
        std::cout << machine.getOutput();
    }

    return 0;
}