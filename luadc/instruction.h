#ifndef LUADC_INSTRUCTION
#define LUADC_INSTRUCTION
#include "opcode.h"
#include <cmath>

enum InstructionArgType {
	iABC,
	iABx,
	iAsBx,
};

#define SIZE_OP 6
#define SIZE_A	8
#define SIZE_B	9
#define SIZE_C	9
#define SIZE_Bx	(SIZE_C + SIZE_B)

#define MAXARG_Bx        ((1<<SIZE_Bx)-1)
#define MAXARG_sBx        (MAXARG_Bx>>1) 

#define POS_OP	0
#define POS_A	(POS_OP + SIZE_OP)
#define POS_C	(POS_A + SIZE_A)
#define POS_B	(POS_C + SIZE_C)
#define POS_Bx	(POS_C)

#define MASK(n,p)      ((~((~(int)0)<<n))<<p)

#define GET_OPCODE(i)   ((i)>>POS_OP) & MASK(SIZE_OP,0)

#define GETARG_A(i)     ((int)((i)>>POS_A) & MASK(SIZE_A,0))
#define GETARG_B(i)     ((int)((i)>>POS_B) & MASK(SIZE_B,0))
#define GETARG_C(i)     ((int)((i)>>POS_C) & MASK(SIZE_C,0))

#define GETARG_Bx(i)    ((int)((i)>>POS_Bx) & MASK(SIZE_Bx,0))
#define GETARG_sBx(i)	(GETARG_Bx(i) - MAXARG_sBx)


#endif