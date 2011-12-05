---
title: A gentle introduction to integrating Lua
kind: article
created_at: 2011-12-05
---

### Introduction
To introduce a scripting language into your project can be a huge
boost in productivity. Interpreted languages run slower than compiled
C/C++ code but the win you make in productivity and rapid development
will be larger.

### Lua
Lua is a scripting language implemented in pure ANSI C. It is
extremely well implemented, lightweight, efficient and has one of the
cleanest API:s that I have ever seen. Surely there are other scripting
languages that can be agood alternative depending on the
application. Python and Javascript are two other examples. However, my
idea is to let this post be the first in a small series of posts
demonstrating some bits of integrating Lua into your C/C++ projects.

This series will NOT be an introduction to Lua as a language but
rather its C API. For a reference of the language, refer to [](lua.org
"http://lua.org").

Worth to note is also that i am using the Lua 5.2 release candidate (rc5)
and there can be some minor differences in the API.

### A simple hello world
To start with, download the Lua source code and compile a static or
dynamic library that you will then link to your application.

To start, we create a simple lua script that does nothing useful at
all but nonetheless.

    #!lua
	function hello()
	    print("Hello Lua!")
    end
	
This simple function just prints "Hello Lua!" in the console. Save the
file as hello.lua (the code below assumes that it is saved in the same
directory as the C/C++ file).

---

So, now for the C/C++ code.

we start by creating a C/C++ file and importing the necessary Lua
libraries. A C++ header `lua.hpp` exists where the necessary Lua C
header files have been wrapped with `extern "C"`.

We can then proceed to creating the lua state by calling
`luaL_newstate()` which returns a pointer to a `lua_State`. The Lua
state is a representation of the state of the Lua interpreter and need
to be passed as the first parameters to all API functions except for
the functions that create states (like `luaL_newstate()`).

Next, we intitalize the standard Lua libraries which may be
unnecessary to do what we will do in this tutorial but it will be
needed in later tutorials.

    #!cplusplus
    int main()
    {
        // Create a new lua state
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
		
        // ...

We should probably also check that `luaL_newstate()` succeeded by
checking that the `L != NULL` but we do not do it here.

After the state has been created, we try to load and run the file we
created earlier.

    #!cplusplus
	// Try to read the file
	if (luaL_dofile(L, "hello.lua") != 0)
	{
        printf("Lua error: %s\n", lua_tostring(L, -1));
        return 1;
	}

`luaL_dofile` is supplied the path of the file and will return 0 if it
succeeds.

The error checking will need some explanation. All communication
between Lua and C happends with a stack-like structure. This stack can
be indexed with positive indices with an index of 1 meaning the lowest
element in the stack and a negative index of -1 meaning the top of the
stack.

If `luaL_dofile` fails in reading the file, it will push an error
message (a string) onto the stack. Therfore we can retrieve this
message by converting the top of the stack into a string.

If `luaL_dofile` succeeds, we can start executing the function.

    #!cplusplus
	// Execute hello function
	lua_getglobal(L, "hello");

	// hello() function is now on top of the stack (-1)
	// Execute it with 0 arguments, 0 return values and
	// the standard error function (0).
	if (lua_pcall(L, 0, 0, 0) != 0)
	{
        printf("Lua error executing hello(): %s\n", 
            lua_tostring(L, -1));
        
        return 1;
	}
	
First we obtain the global function called "hello" that we created
earlier. This puts this function on top of the stack. The function is
then executed with `lua_pcall`. The parameters are in turn the Lua
state `L`, that we supply 0 arguments, expect 0 return values and
that lua should use the standard error handler.

For handling errors, we use the same scheme as with `luaL_dofile`.

This is actually it. If you execute this, you should get `Hello Lua!`
printed in the console.

Next time, we will define C functions that are callable from Lua.
