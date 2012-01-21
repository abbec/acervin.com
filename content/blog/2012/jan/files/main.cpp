// The C++ header file if you compiled
// Lua as C (or use extern "C").
#include "lua.hpp"
#include <cstdio>

int lua_add(lua_State *L)
{
	// Check the number of arguments
	int argc = lua_gettop(L);
	if (argc != 2)
	{
		luaL_error(L, "Wrong number of arguments for add, expected 2, got %d", argc);
		return 0;
	}

	// Obtain arguments
	int a = luaL_checkinteger(L, 1) + luaL_checkinteger(L, 2);
	lua_pushnumber(L, a);

	// We have pushed one value
	// onto the stack
	return 1;
}


int main()
{
	// Create a new lua state
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	// Register our add function
	lua_register(L, "add", lua_add);

	// Try to read the file
	if (luaL_dofile(L, "hello.lua") != 0)
	{
		printf("Lua error: %s\n", lua_tostring(L, -1));
		getc(stdin);
		return 1;
	}

	// Execute hello function
	lua_getglobal(L, "hello");

	// hello() function is now on top of the stack (-1)
	// Execute it with 0 arguments, 0 return values and
	// the standard error function (0).
	if (lua_pcall(L, 0, 0, 0) != 0)
	{
		printf("Lua error executing hello(): %s\n", lua_tostring(L, -1));
		getc(stdin);
		return 1;
	}

	getc(stdin);
	lua_close(L);

	return 0;
}