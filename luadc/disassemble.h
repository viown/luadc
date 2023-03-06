#ifndef LUADC_LUABYTECODE
#define LUADC_LUABYTECODE
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "header.h"
#include "opcode.h"

enum ConstantType : unsigned char {
	LUA_TNIL=0,
	LUA_TBOOLEAN=1,
	LUA_TNUMBER=3,
	LUA_TSTRING=4,
};

struct String {
	size_t length;
	char* string;
};

struct Constant {
	ConstantType type;
	union {
		/* 
		* A nil value is not included because it only holds a single value
		* which `type` represents
		*/
		bool boolean;
		double number;
		String string;

	};
};

struct Instruction {
	Opcode opcode;
	int A;
	int B;
	int C;

	int Bx;
	int sBx;
};

struct InstructionList {
	int instruction_size;
	std::vector<Instruction> instructions;
};

struct ConstantList {
	size_t constant_size; /* sizek */
	std::vector<Constant> constants;
};

struct SourcelinePositionList {
	int sizelineinfo;
	std::vector<int> positions;
};

struct Local {
	String local_variable_name;
	int start_var_scope;
	int end_var_scope;
};

struct LocalList {
	int sizelocvars;
	std::vector<Local> locals;
};

struct UpvalueList {
	int sizeupvalues;
	std::vector<String> upvalue_name;
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

	size_t function_prototypes_size;
	std::vector<FunctionBlock> function_prototypes;

	/* debug info */
	SourcelinePositionList source_line_position_list;
	LocalList local_list;
	UpvalueList upvalue_list;
	
};


struct LuaPrototype {
	std::vector<unsigned char> bytecode;

	LuaHeader header;
	FunctionBlock function_block; /* top-level function */
};

LuaPrototype parseFile(std::string filename);
FunctionBlock parseFunctionBlock(unsigned char* block);
void disassemble_output(LuaPrototype prototype);

#endif