
#include <iostream>
#include "Cpu.h"
#include "Assembler.h"


using std::cout;
using std::endl;

int main()
{
	Assembler assembler;
    Cpu cpu;

	std::vector<std::string> prog = assembler.readFile("program.txt");
	std::vector<int> ROM = assembler.assemble(prog);

	
        
    cpu.init();
    cpu.loadRAM(ROM);

	while(cpu.isRunning)
	{
		cpu.fetch();
		cpu.dump();
	}
	
	
	

    
    
    
    return 0;

}
