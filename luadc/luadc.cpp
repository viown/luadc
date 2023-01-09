#include <iostream>
#include <inttypes.h>
#include "Opcode.h"

int main()
{
    Opcode opcode = VARARG;
    std::cout << static_cast<int>(opcode);

    return 0;
}