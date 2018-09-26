#include "stdafx.h""
#include <stdint.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Cpu.h"
#include <bitset>

using std::string;
using std::cout;
using std::endl;
using std::bitset;




Cpu::Cpu()
{
    //Word w;
    //w.word = 0x2A5C;
    //printf("%04x ", w.bits.b6);
}

void Cpu::init()
{
    isRunning = true;
    PC = PC_START;
    
    //clear RAM
    for(int i = 0; i < RAM_SIZE; i++)
    {
        ram[i].word = 0;
    }
    
    //clear registers
    for(int i = 0; i < NUM_REGISTERS; i++)
    {
        R[i].word = 0;
    }
}

void Cpu::loadRAM()
{
    //ram[0].word = 0x1040;
    //ram[1].word = 0x000F;

	
	//HALT 0x0000 opcode = 0000 0000 0000 0000 = 0x0000
	//SET 0x0001 opcode = 0000 1000 0000 0000 = 0x0800
	//ADD 0x0002 opcode = 0001 0000 0000 0000 = 0x1000
	//SUB 0x0003 opcode = 0001 1000 0000 0000 = 0x1800
	//MUL 0x0004 opcode = 0010 0000 0000 0000 = 0x2000
	//DIV 0x0005 opcode = 0010 1000 0000 0000 = 0x2800


	//SET register 0 to 5
	ram[0].word = 0x0001; //SET opcode
	ram[1].word = 0x0005; 

	//ADD 3 to register 0
	ram[2].word = 0x0002; //ADD opcode
	ram[3].word = 0x0003;

	//MUL register 0 by 7
	ram[4].word = 0x0004; //MUL opcode
	ram[5].word = 0x0007;

	//DIV register 0 by 2
	ram[6].word = 0x0005; //DIV opcode
	ram[7].word = 0x0002;

	//0000 0001 0100 0110
	//bitwise AND reg & reg2
	ram[8].word = 0x0001; //SET reg0
	ram[9].word = 0x0005; // to 5
	ram[10].word = 0x0006; //AND reg0 & 4
	ram[11].word = 0x0004;
	
	//0100
	//1001
	//1101
	ram[12].word = 0x0007;//OR reg0
	ram[13].word = 0x0009;//with 9

	//1101
	//1111
	//0010
	ram[14].word = 0x0008;//XOR reg0 
	ram[15].word = 0x000F;//with 15

	//0010 = F
	//1000
	ram[16].word = 0x0009;//SHL reg0 
	ram[17].word = 0x0002;//with 2

	//0000 1000
	//0000 0100
	//0001 0000
	ram[18].word = 0x000A;//SHR reg0 
	ram[19].word = 0x0001;//with 1

	ram[20].word = 0x000B;//MOD reg0 
	ram[21].word = 0x0002;//with 2
	/*
	ram[22].word = 0x000C;//JMP 
	ram[23].word = 0x0080;//to address 128*/

	ram[22].word = 0x0001;//SET reg0 
	ram[23].word = 0x0007;//to 7
	ram[24].word = 0x000F;//JGEZ 
	ram[25].word = 0x0100;//address 256


	ram[26].word = 0x0000; //HALT


}

void Cpu::fetch()
{
    Word instruction = ram[PC];
    Word value = ram[PC + 1];

    cout << "Instruction: ";
    printf("%04x ", instruction.word);

    cout << "Value: ";
    printf("%04x ", value.word);
    cout << endl;

	
	decode(instruction, value);
	
    

    
}

void Cpu::decode(Word instruction, Word value)
{
     cout << "Decoding...";
     bitset<16> bitset(instruction.instruction.opcode);
     std::cout << bitset << endl;


		 switch (instruction.instruction.opcode)
		 {
			 cout << endl;

		 case 0x0000:
			 cout << "HALT" << endl;
			 HALT();
			 break;

		 case 0x0001:
			 cout << "SET" << endl;
			 SET(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0002:
			 cout << "ADD" << endl;
			 ADD(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0003:
			 cout << "SUB" << endl;
			 SUB(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0004:
			 cout << "MUL" << endl;
			 MUL(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0005:
			 cout << "DIV" << endl;
			 DIV(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0006:
			 cout << "AND" << endl;
			 AND(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0007:
			 cout << "OR" << endl;
			 OR(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0008:
			 cout << "XOR" << endl;
			 XOR(instruction.instruction.source_register, value.word);
			 break;

		 case 0x0009:
			 cout << "SHL" << endl;
			 SHL(instruction.instruction.source_register, value.word);
			 break;

		 case 0x000A:
			 cout << "SHR" << endl;
			 SHR(instruction.instruction.source_register, value.word);
			 break;

		 case 0x000B:
			 cout << "MOD" << endl;
			 MOD(instruction.instruction.source_register, value.word);
			 break;

		 case 0x000C:
			 cout << "JMP" << endl;
			 JMP(value.word);
			 break;

		 case 0x000D:
			 cout << "JE" << endl;
			 JE(value.word);
			 break;

		 case 0x000E:
			 cout << "JNE" << endl;
			 JNE(value.word);
			 break;

		 case 0x000F:
			 cout << "JGEZ" << endl;
			 JGEZ(value.word, instruction.instruction.source_register);
			 break;

		 case 0x0010:
			 cout << "CMP" << endl;
			 CMP(instruction.instruction.source_register, value.word);
			 break;
		 }
	 
    
    
}

//TODO:
void Cpu::NOP()
{
	//add R0, 0, 0
}

//End program
void Cpu::HALT()
{
    isRunning = false;
}

void Cpu::SET(u16 x, u16 v)
{
    R[x].word = v;
    PC += 2;
}





/**
* Set Rx = Rx + v.
* Adds the value v to the value of register Rx, then stores the result in Rx. 
*/
void Cpu::ADD(u16 x, u16 v)
{
    R[x].word = R[x].word + v;
    PC += 2;
}

/**
* Set Rx = Rx - vv.
* * Subtracts the value v from the value of register Rx, then stores the result in Rx. 
*/
void Cpu::SUB(u16 x, u16 v)
{
    R[x].word = R[x].word - v;
    PC += 2;
}

/**
* Set Rx = Rx * v.
* Multiplies the value v by the value of register Rx, then stores the result in Rx.
*/
void Cpu::MUL(u16 x, u16 v)
{
	R[x].word = R[x].word * v;
	PC += 2;
}

/**
* Set Rx = Rx * v.
* Divides the value of register Rx by value v, then stores the result in Rx.
*/
void Cpu::DIV(u16 x, u16 v)
{
	R[x].word = R[x].word / v;
	PC += 2;
}

void Cpu::AND(u16 x, u16 v)
{
	R[x].word = R[x].word & v;
	PC += 2;
}

void Cpu::OR(u16 x, u16 v)
{
	R[x].word = R[x].word | v;
	PC += 2;
}

void Cpu::XOR(u16 x, u16 v)
{
	R[x].word = R[x].word ^ v;
	PC += 2;
}

void Cpu::SHL(u16 x, u16 v)
{
	R[x].word = R[x].word << v;
	PC += 2;
}

void Cpu::SHR(u16 x, u16 v)
{
	R[x].word = R[x].word >> v;
	PC += 2;
}

void Cpu::MOD(u16 x, u16 v)
{
	R[x].word = R[x].word % v;
	PC += 2;
}

void Cpu::JMP(u16 address)
{
	PC = address;
}

//TODO:: figure out how I want to handle this
void Cpu::JE(u16 address)
{
	if (flags.Z)
	{
		PC = address;
	}
	else
	{
		PC += 2;
	}
	
}

void Cpu::JNE(u16 address)
{
	if (!flags.Z)
	{
		PC = address;
	}
	else
	{
		PC += 2;
	}

}

void Cpu::JGEZ(u16 address, u16 x)
{
	if (R[x].word >= 0)
	{
		PC = address;
	}
	else
	{
		PC += 2;
	}
}

void Cpu::CMP(u16 x, u16 v)
{
	if (R[x].word - v == 0)
	{
		flags.Z = 1;
	}
	
	PC += 2;
}

void Cpu::dump()
{
    cout << "PC:" << this->PC << endl;
    //printf("%u", (unsigned int)this->SP);
    cout << endl;
    
    for(int i = 0; i < NUM_REGISTERS; i++)
    {
        cout << "R" << i << ":";
        printf("0x%04x ", R[i].word);
        cout << endl;
    }

	cout << endl;
}

Cpu::~Cpu()
{

}
