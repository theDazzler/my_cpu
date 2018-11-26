#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Assembler.h"
#include "Cpu_types.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

using namespace std;

//const string Assembler::COMMENT_SYMBOL = ";";

Assembler::Assembler()
{

}

std::vector<std::string> Assembler::readFile(std::string filename)
{
    std::vector<std::string> lines;

    cout << "Reading file " << filename << endl;
    string line;
    ifstream myfile;
    myfile.open(filename);

   if(!myfile.is_open())
    {
      perror("Error open");
      exit(EXIT_FAILURE);
   }
    while(getline(myfile, line)) 
    {
        lines.push_back(line);
        cout << line << endl;
    }
    myfile.close();

    cout << lines.size() << endl;

    return lines;
}

std::vector<int> Assembler::assemble(std::vector<std::string> &instructions)
{
    

    vector<string> myTokens;
    int j =0;

    //for each line i.e ADD R1, R2
    for(int i=0; i < instructions.size(); i++)
    {
       

        //cout << "ty: " << instructions.at(i) << endl;

        istringstream ss(instructions.at(i));
        string token;
        //Separate string based on commas and white spaces
        getline(ss,token,' ');
        myTokens.push_back(token);
        cout << "space: " << myTokens[j] << endl;
        j++;

        while (getline(ss, token,',')){
            ss.ignore();
            myTokens.push_back(token);
            cout << "comma:" << myTokens[j] << endl;
            j++;
        }

        string opcode = myTokens.at(i);
        

        assembleOpcode(instructions.at(i).substr(0, instructions.at(i).find(" ")), i, myTokens);


    }

    return this->romInstructions;



}

//000a asss dddo oooo
void Assembler::assembleOpcode(std::string opcode, int lineNumber, std::vector<std::string> &tokens)
{
    
    cout << "Assembling opcode " << opcode << endl;

    //SET R1, 10
    if(opcode.compare("SET") == 0)
    {
        twoOperandInstruction(0x0001, lineNumber, tokens);
        
    }
    //ADD R1, 5
    else if(opcode.compare("ADD") == 0)
    {
        //for example, tokens = {"ADD", "R1", "5"}
        twoOperandInstruction(0x0002, lineNumber, tokens);
        
    }

    //SUB R1, 5
    else if(opcode.compare("SUB") == 0)
    {
        twoOperandInstruction(0x0003, lineNumber, tokens);
        
    }

    //MUL R1, 5
    else if(opcode.compare("MUL") == 0)
    {
        twoOperandInstruction(0x0004, lineNumber, tokens);
        
    }

    //DIV R1, 5
    else if(opcode.compare("DIV") == 0)
    {
        twoOperandInstruction(0x0005, lineNumber, tokens);
        
    }

    //AND R1, 5
    else if(opcode.compare("AND") == 0)
    {
        twoOperandInstruction(0x0006, lineNumber, tokens);
        
    }

    //OR R1, 5
    else if(opcode.compare("OR") == 0)
    {
        twoOperandInstruction(0x0007, lineNumber, tokens);
        
    }

    //XOR R1, 5
    else if(opcode.compare("XOR") == 0)
    {
        twoOperandInstruction(0x0008, lineNumber, tokens);
        
    }

    //SHL R1, 2
    else if(opcode.compare("SHL") == 0)
    {
        twoOperandInstruction(0x0009, lineNumber, tokens);
        
    }

    //SHR R1, 2
    else if(opcode.compare("SHR") == 0)
    {
        twoOperandInstruction(0x000A, lineNumber, tokens);
        
    }

    //MOD R1, 2
    else if(opcode.compare("MOD") == 0)
    {
        twoOperandInstruction(0x000B, lineNumber, tokens);
        
    }

    //JMP 0x2031
    else if(opcode.compare("JMP") == 0)
    {
        //twoOperandInstruction(0x0009, lineNumber, tokens);
         Word machineInstruction = {0};//initialization
         machineInstruction.instruction.opcode = 0x000C;
         addInstructionToROM(machineInstruction);
        
    }

    //JE 0x2031
    else if(opcode.compare("JE") == 0)
    {
        //twoOperandInstruction(0x0009, lineNumber, tokens);
         Word machineInstruction = {0};//initialization
         machineInstruction.instruction.opcode = 0x000D;
         addInstructionToROM(machineInstruction);
        
    }

    //JNE 0x2031
    else if(opcode.compare("JNE") == 0)
    {
        //twoOperandInstruction(0x0009, lineNumber, tokens);
         Word machineInstruction = {0};//initialization
         machineInstruction.instruction.opcode = 0x000E;
         addInstructionToROM(machineInstruction);
        
    }

    //JGEZ 0x2031, R1
    else if(opcode.compare("JGEZ") == 0)
    {
        int numTokensPerLine = 3;
        int addressOffset = 1;
        int valueOffset = 2;

        string address = tokens.at(numTokensPerLine * lineNumber + addressOffset);
        string sourceRegister = tokens.at(numTokensPerLine * lineNumber + valueOffset);

        //twoOperandInstruction(0x0009, lineNumber, tokens);
        Word machineInstruction = {0};//initialization
        machineInstruction.instruction.opcode = 0x000F;
        machineInstruction.instruction.source_register = REGISTER_MAP.at(sourceRegister);
        addInstructionToROM(machineInstruction);

        Word valueInstruction = {0};
        stringstream intValue(address); 
        int x = 0;
        intValue >> x;
        valueInstruction.word = x;

        addInstructionToROM(machineInstruction);
        
    }

    //CMP R1, 8
    else if(opcode.compare("JGEZ") == 0)
    {
        int numTokensPerLine = 3;
        int srcRegOffset = 1;
        int valueOffset = 2;

        string sourceRegister = tokens.at(numTokensPerLine * lineNumber + srcRegOffset);
        string value = tokens.at(numTokensPerLine * lineNumber + valueOffset);

        //twoOperandInstruction(0x0009, lineNumber, tokens);
        Word machineInstruction = {0};//initialization
        machineInstruction.instruction.opcode = 0x0010;
        machineInstruction.instruction.source_register = REGISTER_MAP.at(sourceRegister);
        addInstructionToROM(machineInstruction);

        Word valueInstruction = {0};
        stringstream intValue(value); 
        int x = 0;
        intValue >> x;
        valueInstruction.word = x;

        addInstructionToROM(machineInstruction);
    }

}
//ex. SET, R1, 10
void Assembler::twoOperandInstruction(u16 opcode, int lineNumber, std::vector<std::string> &tokens)
{
    int numTokensPerLine = 3;
    int sourceRegOffset = 1;
    int valueOffset = 2;

    //for example, tokens = {"SET", "R1", "10"}
    string sourceReg = tokens.at(numTokensPerLine * lineNumber + sourceRegOffset);
    string value = tokens.at(numTokensPerLine * lineNumber + valueOffset);

    Word machineInstruction = {0};
    machineInstruction.instruction.opcode = opcode;
    cout << "DESTINATION REGGGGGG: " << sourceReg << endl;
    machineInstruction.instruction.source_register = REGISTER_MAP.at(sourceReg);
    
    Word valueInstruction = {0};
    stringstream intValue(value); 
    int x = 0;
    intValue >> x;
    valueInstruction.word = x;

    cout << "Machine Instruction: ";
    printf("0x%04x ", machineInstruction.word);
    cout << endl;

    addInstructionToROM(machineInstruction);


    cout << "Value Instruction: ";
    printf("0x%04x ", valueInstruction.word);
    cout << endl;

    addInstructionToROM(valueInstruction);
}

void Assembler::addInstructionToROM(Word instruction)
{
    romInstructions.push_back(instruction.word);
}


Assembler::~Assembler()
{

}

