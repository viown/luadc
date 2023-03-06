#include "disassemble.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

void verify_header(LuaHeader header) {
	if (header.signature != 0x61754C1B) {
		std::cerr << "Invalid signature in bytecode file.\n";
		exit(1);
	}
	else if (header.size_t_size != sizeof(size_t)) {
		/* wrong bit target */
		std::cerr << "size_t mismatch! Expected " << sizeof(size_t) << " instead got " << static_cast<int>(header.size_t_size) << '\n';
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

LuaPrototype parseFile(std::string filename) {
	LuaPrototype prototype;

	std::fstream file(filename);

	int currentByte = 0;
	while ((currentByte = file.get()) != -1) {
		prototype.bytecode.push_back(currentByte);
	}

	file.close();

	memcpy((unsigned char*)&prototype.header, &prototype.bytecode[0], 12);
	verify_header(prototype.header);

	prototype.function_block = parseFunctionBlock(&prototype.bytecode[12]);

	return prototype;
}

/* output disassembled code */
void disassemble_output(LuaPrototype prototype) {

	std::cout << "Source name: " << prototype.function_block.source_name.string << '\n';

	std::cout << '\n';

	std::cout << "; constants\n";
	for (size_t i = 0; i < prototype.function_block.constant_list.constant_size; ++i) {
		Constant constant = prototype.function_block.constant_list.constants[i];

		if (constant.type == LUA_TNUMBER) {
			std::cout << "CONST (NUMBER, " << constant.number << ")";
		}
		else if (constant.type == LUA_TSTRING) {
			std::cout << "CONST (STRING, \"" << constant.string.string << "\")";
		}
		else if (constant.type == LUA_TNIL) {
			std::cout << "CONST (NIL)";
		}
		else if (constant.type == LUA_TBOOLEAN) {
			std::cout << "CONST (BOOL, " << (constant.boolean ? "true" : "false") << ")";
		}
		std::cout << "\t\t; " << i << "\n";
	}

	std::cout << "\n; code\n";

	std::vector<Instruction> instructions = prototype.function_block.instruction_list.instructions;
	for (int i = 0; i < instructions.size(); ++i) {
		Instruction instruction = instructions[i];
		OpcodeInfo opcode_info = opcodes.at(instruction.opcode);
		if ((i + 1) < 10) {
			std::cout << "[0" << (i + 1) << "] " << opcode_info.name;
		}
		else {
			std::cout << "[" << (i + 1) << "] " << opcode_info.name;
		}
		std::vector<int> arguments;

		switch (opcode_info.arg_type) {
		case iABC:
			arguments.push_back(instruction.A);
			arguments.push_back(instruction.B);
			arguments.push_back(instruction.C);
			break;
		case iABx:
			arguments.push_back(instruction.A);
			arguments.push_back(instruction.Bx);
			break;
		case iAsBx:
			arguments.push_back(instruction.A);
			arguments.push_back(instruction.sBx);
			break;
		}

		if (instruction.opcode == JMP) {
			/* print sBx only */
			std::cout << "\t" << arguments[1];
		}
		else if (instruction.opcode == TFORLOOP) {
			/* print A and C only */
			std::cout << "\t" << arguments[0] << "\t\t" << arguments[2];
		}
		else {
			for (int i = 0; i < arguments.size() && i < opcode_info.arg_size; ++i) {
				std::cout << "\t" << arguments[i];
			}
		}
		std::cout << "\n";

	}
}

FunctionBlock parseFunctionBlock(unsigned char* block) {
	FunctionBlock function_block;

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
		/*
		Each instruction is 32 bits long, but depending on the opcode, they may be encoded differently.
		*/
		int instruction_loc = start_of_instructions + (i * 4);
		int v;
		memcpy(&v, &block[instruction_loc], 4);
		Instruction instruction;

		instruction.opcode = static_cast<Opcode>(GET_OPCODE(v));
		instruction.A = GETARG_A(v);
		instruction.B = GETARG_B(v);
		instruction.C = GETARG_C(v);
		instruction.Bx = GETARG_Bx(v);
		instruction.sBx = GETARG_sBx(v);

		function_block.instruction_list.instructions.push_back(instruction);
	}

	/* copy constants */

	int loc_constant_size = start_of_instructions + (function_block.instruction_list.instruction_size * 4);
	int loc_constant_list = loc_constant_size + 4;

	memcpy(&function_block.constant_list.constant_size, &block[loc_constant_size], 4);

	unsigned char* constant_addr = block + loc_constant_list;

	for (int i = 0; i < function_block.constant_list.constant_size; ++i) {
		Constant constant;
		ConstantType constantType = *(ConstantType*)constant_addr;
		constant.type = constantType;

		constant_addr += 1;
		
		if (constantType == LUA_TNUMBER) {
			constant.number = *(double*)constant_addr;
			constant_addr += 8;
		}
		else if (constantType == LUA_TBOOLEAN) {
			constant.boolean = *(unsigned char*)constant_addr;
			constant_addr += 1;
		}
		else if (constantType == LUA_TSTRING) {
			size_t string_size = *(size_t*)constant_addr;
			constant_addr += sizeof(size_t);
			char* string = (char*)constant_addr;
			constant.string.length = string_size;
			constant.string.string = string;

			constant_addr += string_size;
		}
		// LUA_TNIL does not have a constant and is represented by constantType

		function_block.constant_list.constants.push_back(constant);
	}

	unsigned char* prototype = constant_addr;

	memcpy(&function_block.function_prototypes_size, prototype, sizeof(size_t));

	prototype += sizeof(size_t);

	for (size_t i = 0; i < function_block.function_prototypes_size; ++i) {
		FunctionBlock b = parseFunctionBlock(prototype);
	}

	return function_block;
}