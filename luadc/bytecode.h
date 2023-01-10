#ifndef LUADC_LUABYTECODE
#define LUADC_LUABYTECODE
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "header.h"
#include "opcode.h"

enum ConstantType : unsigned char {
	LUA_TNIL,
	LUA_TBOOLEAN,
	LUA_TNUMBER,
	LUA_TSTRING
};

struct String {
	size_t length;
	char* string;
};

struct Constant {
	ConstantType constant_type;
	union {
		/* 
		* A nil value is not included because it only holds a singular value
		* which constant_type holds
		*/
		bool boolean;
		double number;
		String string;

	};
};


struct InstructionList {
	int instruction_size;
	std::vector<int> instructions;
};

struct ConstantList {
	size_t constant_size; /* sizek */
	std::vector<Constant> constants;
};

struct FunctionBlock {
	String source_name;

	int line_defined;
	int last_line_defined;
	unsigned char upvalue_count;
	unsigned char parameter_count;
	unsigned char is_vararg;
	unsigned char maximum_stack_size;

	InstructionList instruction_list;
	ConstantList constant_list;

	int function_blocks_size;
	std::vector<FunctionBlock> function_blocks;
	
};

class LuaBytecode {
private:
	std::vector<unsigned char> bytecode;

	LuaHeader header;
	FunctionBlock function_block; /* top-level function */
public:
	LuaBytecode(std::string file);

	LuaHeader get_header() { return this->header; }

	FunctionBlock parseFunctionBlock(int addr);
};

#endif