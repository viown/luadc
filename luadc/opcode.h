#ifndef LUADC_OPCODE
#define LUADC_OPCODE
#include "instruction.h"
#include <map>
#include <string>

enum Opcode : unsigned char {
	MOVE,		// 0
	LOADK,		// 1
	LOADBOOL,	// 2
	LOADNIL,	// 3
	GETUPVAL,	// 4
	GETGLOBAL,	// 5
	GETTABLE,	// 6
	SETGLOBAL,	// 7
	SETUPVAL,	// 8
	SETTABLE,	// 9
	NEWTABLE,	// 10
	SELF,		// 11
	ADD,		// 12
	SUB,		// 13
	MUL,		// 14
	DIV,		// 15
	MOD,		// 16
	POW,		// 17
	UNM,		// 18
	NOT,		// 19
	LEN,		// 20
	CONCAT,		// 21
	JMP,		// 22
	EQ,			// 23
	LT,			// 24
	LE,			// 25
	TEST,		// 26
	TESTSET,	// 27
	CALL,		// 28
	TAILCALL,	// 29
	RETURN,		// 30
	FORLOOP,	// 31
	FORPREP,	// 32
	TFORLOOP,	// 33
	SETLIST,	// 34
	CLOSE,		// 35
	CLOSURE,	// 36
	VARARG		// 37
};

struct OpcodeInfo {
	std::string name;
	InstructionArgType arg_type;
	int arg_size;
};

static const std::map<Opcode, OpcodeInfo> opcodes = {
	{MOVE,		{"MOVE",		iABC,	2}},
	{LOADK,		{"LOADK",		iABx,	2}},
	{LOADBOOL,	{"LOADBOOL",	iABC,	3}},
	{LOADNIL,	{"LOADNIL",		iABC,	2}},
	{GETUPVAL,	{"GETUPVAL",	iABC,	2}},
	{GETGLOBAL, {"GETGLOBAL",	iABx,	2}},
	{GETTABLE,	{"GETTABLE",	iABC,	3}},
	{SETGLOBAL, {"SETGLOBAL",	iABx,	2}},
	{SETUPVAL,	{"SETUPVAL",	iABC,	2}},
	{SETTABLE,	{"SETTABLE",	iABC,	3}},
	{NEWTABLE,	{"NEWTABLE",	iABC,	3}},
	{SELF,		{"SELF",		iABC,	3}},
	{ADD,		{"ADD",			iABC,	3}},
	{SUB,		{"SUB",			iABC,	3}},
	{MUL,		{"MUL",			iABC,	3}},
	{DIV,		{"DIV",			iABC,	3}},
	{MOD,		{"MOD",			iABC,	3}},
	{POW,		{"POW",			iABC,	3}},
	{UNM,		{"UNM",			iABC,	2}},
	{NOT,		{"NOT",			iABC,	2}},
	{LEN,		{"LEN",			iABC,	2}},
	{CONCAT,	{"CONCAT",		iABC,	3}},
	{JMP,		{"JMP",			iAsBx,	1}},
	{EQ,		{"EQ",			iABC,	3}},
	{LT,		{"LT",			iABC,	3}},
	{LE,		{"LE",			iABC,	3}},
	{TEST,		{"TEST",		iABC,	2}},
	{TESTSET,	{"TESTSET",		iABC,	3}},
	{CALL,		{"CALL",		iABC,	3}},
	{TAILCALL,	{"TAILCALL",	iABC,	3}},
	{RETURN,	{"RETURN",		iABC,	2}},
	{FORLOOP,	{"FORLOOP",		iAsBx,	2}},
	{FORPREP,	{"FORPREP",		iAsBx,	2}},
	{TFORLOOP,	{"TFORLOOP",	iABC,	2}},
	{SETLIST,	{"SETLIST",		iABC,	3}},
	{CLOSE,		{"CLOSE",		iABC,	1}},
	{CLOSURE,	{"CLOSURE",		iABx,	2}},
	{VARARG,	{"VARARG",		iABC,	2}}
};

#endif