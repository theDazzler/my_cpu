#ifndef CPU_HH
#define CPU_HH

class Cpu
{
    typedef uint_least16_t u16;
    typedef uint_least8_t u8;

    static const int RAM_SIZE = 65536; //4K
    static const int NUM_REGISTERS = 8;
    static const int PC_START = 0x0000;

	struct
	{
		u8 C : 1; //carry flag
		u8 Z : 1; //zero flag
		u8 A : 1; //not used
		u8 B : 1;//not used
		u8 N : 1;//not used
		u8 D : 1;//not used
		u8 W : 1;//not used
		u8 X : 1;//not used
	} flags;
    
    

    union Word
    {
        //lsb is b1 (rightmost bit)
        //0000 0000 0000 0001
        struct
        {
            u16 b1:1;
            u16 b2:1;
            u16 b3:1;
            u16 b4:1;
            u16 b5:1;
            u16 b6:1;
            u16 b7:1;
            u16 b8:1;
            u16 b9:1;
            u16 b10:1;
            u16 b11:1;
            u16 b12:1;
            u16 b13:1;
            u16 b14:1;
            u16 b15:1;
            u16 b16:1;

        } bits;

        struct
        {
            u16 n1:4;
            u16 n2:4;
            u16 n3:4;
            u16 n4:4;
        } nibbles;

        struct 
        {
            u16 b1;
            u16 b2;
        } bytes;

        struct
        {
			u16 opcode : 5;
			u16 destination_register : 3;
			u16 source_register : 3;     
            u16 addressing_mode:2;
			u16 undefined : 3;
            
        } instruction;
        u16 word;
    };
    
    

    public:
        Word ram[RAM_SIZE];
        Word R[NUM_REGISTERS];
        u16 PC;
        bool isRunning;

        Cpu();
        virtual ~Cpu();

        void init();
        void loadRAM();
        void cycle();
        void fetch();
        void decode(Word instruction, Word value);

		void NOP();
    
        void HALT();

        /**
		* Set Rx = v.
		* Put the value v into register Rx.
		*/
        void SET(u16 x, u16 v);

        /**
		* Set Rx = Rx + v.
		* Adds the value v to the value of register Rx, then stores the result in Rx. 
		*/
        void ADD(u16 x, u16 v);

         /**
		* Set Rx = Rx - v.
		* Subtracts the value v from the value of register Rx, then stores the result in Rx. 
		*/
        void SUB(u16 x, u16 v);

		/**
		* Set Rx = Rx * v.
		* Multiplies the value v by the value of register Rx, then stores the result in Rx.
		*/
		void MUL(u16 x, u16 v);

		/**
		* Set Rx = Rx * v.
		* Divides the value of register Rx by value v, then stores the result in Rx.
		*/
		void DIV(u16 x, u16 v);

		/**
		* Set Rx = Rx & v.
		* Bitwise AND
		* 
		*/
		void AND(u16 x, u16 v);

		/**
		* Set Rx = Rx | v.
		* Bitwise OR
		*
		*/
		void OR(u16 x, u16 v);
		
		/**
		* Set Rx = Rx ^ v.
		* Bitwise XOR
		*
		*/
		void XOR(u16 x, u16 v);

		/**
		* Set Rx = Rx << v.
		* Shift Left
		*
		*/
		void SHL(u16 x, u16 v);

		/**
		* Set Rx = Rx >> v.
		* Shift Right
		*
		*/
		void SHR(u16 x, u16 v);

		/**
		* Set Rx = Rx % v.
		*
		*/
		void MOD(u16 x, u16 v);

		/**
		* Jump to address
		*
		*/
		void JMP(u16 address);

		/**
		* Jump to address if Rx == v
		*
		*/
		void JE(u16 address);

		/**
		* Jump to address if Rx != v
		*
		*/
		void JNE(u16 address);

		/**
		* Jump to address if Rx >= 0
		*
		*/
		void JGEZ(u16 address, u16 x);

		void CMP(u16 x, u16 v);

		

        void dump();

    private:


};

#endif
