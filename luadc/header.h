#ifndef LUADC_LUAHEADER
#define LUADC_LUAHEADER

struct LuaHeader {
	int signature; /* should be \x27Lua or 0x61754C1B */

	/* Lua version. Currently only 0x51 (Lua 5.1) is supported. */
	unsigned char version;

	unsigned char format_version; /* Should be 0 */

	unsigned char endianness;

	unsigned char int_size;

	/*
	* The size of size_t is 4 bytes if the bytecode was compiled through 32 bit Lua. Otherwise
	* the size will be 8. By default, luadc is compiled through x86 which can only support 32-bit bytecode.
	* Compile luadc with x64 to support decompilation for 64-bit bytecode.
	*/
	unsigned char size_t_size;
	unsigned char instruction_size;
	unsigned char lua_number_size;
	unsigned char integral_flag;
};

#endif