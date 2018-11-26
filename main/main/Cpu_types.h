#pragma once

#include "stdint.h"

typedef uint_least16_t u16;
typedef uint_least8_t u8;

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