# my_cpu 
## CPU SPECS

16 bit words</br> 
65536 words RAM (4k)</br> 
PC - 16 bit</br> 
SP</br> 
</br> 
Stack starts at end of RAM and grows downwards</br> 
</br> 
o = opcode, a = addressing mode, s = source register, d = dest register</br> 
v = value</br> 
</br> 
000a asss dddo oooo</br> 
vvvv vvvv vvvv vvvv</br> 
</br> 
## OPCODES</br> 
0x00 - HALT</br> 
0x01 - SET R1, 10</br> 
0x02 - ADD</br> 
0x03 - SUB</br> 
0x04</br> 
0x05</br> 
0x06</br> 
</br> 
SET R4, 5</br> 
ADD R4, 8</br> 
SUB R4, 2</br> 
SET R1, 7</br> 
MUL R1, 8</br> 
DIV R1, 2</br> 
</br> 
void NOP();  </br> 
void HALT();</br> 
void SET(u16 x, u16 v);</br> 
void ADD(u16 x, u16 v);</br> 
void SUB(u16 x, u16 v);</br> 
void MUL(u16 x, u16 v);</br> 
void DIV(u16 x, u16 v);</br> 
void AND(u16 x, u16 v);</br> 
void OR(u16 x, u16 v);</br> 
void XOR(u16 x, u16 v);</br> 
void SHL(u16 x, u16 v);</br> 
void SHR(u16 x, u16 v);</br> 
void MOD(u16 x, u16 v);</br> 
void JMP(u16 address);</br> 
void JE(u16 address);</br> 
void JNE(u16 address);</br> 
void JGEZ(u16 address, u16 x);</br> 
void CMP(u16 x, u16 v);</br> 

