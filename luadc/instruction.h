#ifndef LUADC_INSTRUCTION
#define LUADC_INSTRUCTION

#define GET_OPCODE(v) \
			v & ((1 << 6) - 1)

#endif