#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Cpu_types.h"

class Assembler
{
    //static const std::string COMMENT_SYMBOL;

    std::unordered_map<std::string, int> REGISTER_MAP = {
        {"R0",0},
        {"R1",1},
        {"R2",2},
        {"R3",3},
        {"R4",4},
        {"R5",5},
        {"R6",6},
        {"R7",7}

    };

    std::vector<int> romInstructions;//contains machine readable program final output

    public:
        std::vector<std::string> readFile(std::string filename);
        std::vector<int> assemble(std::vector<std::string> &instructions);
        void assembleOpcode(std::string opcode, int lineNumber, std::vector<std::string> &tokens);
        void twoOperandInstruction(u16 opcode, int lineNumber, std::vector<std::string> &tokens);
        void addInstructionToROM(Word instruction);

        Assembler();
        virtual ~Assembler();


    private:
};