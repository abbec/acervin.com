---
title: Integrating Lua (Part 2)
kind: article
publish: true
created_at: 2012-01-22
tags: ['C++', 'Lua']
---

### Calling C functions

In the last tutorial we saw that it was possible to call Lua functions from C (and C++). It is also possible to define functions in C that is callable from Lua.

All C functions that will be callable from Lua follows the same pattern and must have a prototype as specified by `lua_CFunction`.

	#!cplusplus
	typedef int (*lua_CFunction) (lua_State *L);

All C functions get a pointer to the Lua state as parameter and returns an integer representing the number of values that the function pushed to the stack. This means that the function does not need to clean up the stack after it is executed. Lua will automatically remove everything below the results.

### Defining our C function
Our C function will be a simple add function. It is defined as
	
	#!cplusplus
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

		// We have pushed one argument
		// onto the stack
		return 1;
	}

Let's walk it through. The first thing we do is check that we got the correct number of arguments. This is done by a call to `lua_gettop(L)`. This function returns the current top of the Lua stack, i.e. the number of arguments provided to our function. If this number is not 2 we raise an error with `luaL_error()` and return 0 to say that we did not push any values onto the stack.

If the argument count was correct we proceced to the row

	#!cplusplus
	int a = luaL_checkinteger(L, 1) + luaL_checkinteger(L, 2);

`luaL_checkinteger()` checks that the argument at a specified position in the stack is actually a number. Otherwise it returns an error and displays a message. If all is well, the result of the addition is in `a`.

The only thing left now is to push our result value back to Lua. This is done with `lua_pushnumber(L, a)`. We then return 1 to tell Lua that we pushed **one** value onto the stack.

### Time to test
To test this new addition function, the `hello` function in the Lua file (see previous post) is modified to include the row `print("add(2,4) = " .. add(2, 4))`. When building and running the example you should get this output:

	Hello Lua!
	add(2,4) = 6

That's it for now! Next time I will show a way to use Lua with C++ objects.

The two files used in this post can be found here:

- [main.cpp](/blog/2012/jan/files/main.cpp "main.cpp")
- [hello.lua](/blog/2012/jan/files/hello.lua "hello.lua")
