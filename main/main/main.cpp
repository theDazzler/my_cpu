#include "stdafx.h""
#include <iostream>
#include "Cpu.h"

using std::cout;
using std::endl;

int main()
{
    Cpu cpu;
        
    cpu.init();
    cpu.loadRAM();

	while(cpu.isRunning)
	{
		cpu.fetch();
		cpu.dump();
	}
	
	
    
    
    
    return 0;

}
