#include "bytecode.h"
#include <iostream>
#include <stdio.h>

void verify_header(LuaHeader header) {
	if (header.signature != 0x61754C1B) {
		std::cerr << "Invalid signature in bytecode file.\n";
		exit(1);
	}
	else if (header.size_t_size != sizeof(size_t)) {
		std::cerr << "size_t mismatch! Expected " << sizeof(size_t) << " instead got " << header.size_t_size << '\n';
		exit(1);
	}
	else if (header.version != 0x51) {
		std::cerr << "Invalid Lua version. Only Lua 5.1 is supported.\n";
		exit(1);
	}
	else if (header.format_version != 0) {
		std::cerr << "Invalid format version. Expected 0.\n";
		exit(1);
	}
}

LuaBytecode::LuaBytecode(std::string filename) {
	std::fstream file(filename);

	int currentByte = 0;
	while ((currentByte = file.get()) != -1) {
		this->bytecode.push_back(currentByte);
	}

	file.close();

	memcpy((unsigned char*)&this->header, &this->bytecode[0], 12);
	verify_header(this->header);
}

FunctionBlock LuaBytecode::parseFunctionBlock(int addr) {
	FunctionBlock function_block;
	unsigned char* block = &this->bytecode[addr]; /* start of function block */

	memcpy(&function_block.source_name.length, block, sizeof(size_t));

	// Addresses

	int source_name = sizeof(size_t);
	int line_defined = source_name + function_block.source_name.length;
	int last_line_defined = line_defined + 4;
	int upvalue_count = last_line_defined + 4;
	int parameter_count = upvalue_count + 1;
	int is_vararg_flag = parameter_count + 1;
	int maximum_stack_size = is_vararg_flag + 1;
	int instruction_size = maximum_stack_size + 1;
	int start_of_instructions = instruction_size + 4;

	function_block.source_name.string = (char*)&block[source_name];

	memcpy(&function_block.line_defined, &block[line_defined], 4);
	memcpy(&function_block.last_line_defined, &block[last_line_defined], 4);
	function_block.upvalue_count = block[upvalue_count];
	function_block.parameter_count = block[parameter_count];
	function_block.is_vararg = block[is_vararg_flag];
	function_block.maximum_stack_size = block[maximum_stack_size];

	/* copy instructions */

	memcpy(&function_block.instruction_list.instruction_size, &block[instruction_size], 4);

	for (int i = 0; i < function_block.instruction_list.instruction_size; ++i) {
		int instruction_loc = start_of_instructions + (i * 4);
		int instruction = 0;
		memcpy(&instruction, &block[instruction_loc], 4);
		function_block.instruction_list.instructions.push_back(instruction);
	}

	return function_block;
}