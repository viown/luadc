#include <iostream>
#include <inttypes.h>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include "opcode.h"
#include "header.h"
#include "bytecode.h"
#include "instruction.h"

int main(int argc, char** argv)
{
    LuaBytecode b(argv[1]);

    FunctionBlock c = b.parseFunctionBlock(12);

//    std::bitset<32> x(c.instruction_list.instructions[1]);

//    std::cout << x << '\n';
//    int op = GET_OPCODE(c.instruction_list.instructions[1]);
//    std::cout << op;

    return 0;
}