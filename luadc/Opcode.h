#ifndef LUADC_OPCODE
#define LUADC_OPCODE
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

static const std::map<Opcode, std::string> opcode_strings = {
	{MOVE, "MOVE"},
	{LOADK, "LOADK"},
	{LOADBOOL, "LOADBOOL"},
	{LOADNIL, "LOADNIL"},
	{GETUPVAL, "GETUPVAL"},
	{GETGLOBAL, "GETGLOBAL"},
	{GETTABLE, "GETTABLE"},
	{SETGLOBAL, "SETGLOBAL"},
	{SETUPVAL, "SETUPVAL"},
	{SETTABLE, "SETTABLE"},
	{NEWTABLE, "NEWTABLE"},
	{SELF, "SELF"},
	{ADD, "ADD"},
	{SUB, "SUB"},
	{MUL, "MUL"},
	{DIV, "DIV"},
	{MOD, "MOD"},
	{POW, "POW"},
	{UNM, "UNM"},
	{NOT, "NOT"},
	{LEN, "LEN"},
	{CONCAT, "CONCAT"},
	{JMP, "JMP"},
	{EQ, "EQ"},
	{LT, "LT"},
	{LE, "LE"},
	{TEST, "TEST"},
	{TESTSET, "TESTSET"},
	{CALL, "CALL"},
	{TAILCALL, "TAILCALL"},
	{RETURN, "RETURN"},
	{FORLOOP, "FORLOOP"},
	{TFORLOOP, "TFORLOOP"},
	{SETLIST, "SETLIST"},
	{CLOSE, "CLOSE"},
	{CLOSURE, "CLOSURE"},
	{VARARG, "VARARG"}
};

#endif