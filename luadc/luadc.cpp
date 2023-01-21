#include <iostream>
#include <inttypes.h>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include "opcode.h"
#include "header.h"
#include "disassemble.h"
#include "instruction.h"


int main(int argc, char** argv)
{
    LuaPrototype b(argv[1]);

    b.disassemble_output();
    return 0;
}