#include "raylib.h"
#include "raylua.h"

void LuaSetGlobalCFunction(LuaState* L, const char* name, LuaCFunction f)
{
    // Push the pointer to function
    lua_pushcfunction(L, f);

    // Get the value on top of the stack
    // and set as a global, in this case is the function
    lua_setglobal(L, name);
}

void LuaSetGlobalInteger(LuaState* L, const char* name, int n)
{
    // Push the integer
    lua_pushinteger(L, n);

    // Get the value on top of the stack
    // and set as a global, in this case is the function
    lua_setglobal(L, name);
}

void LuaSetGlobalNumber(LuaState* L, const char* name, double n)
{
    // Push the number
    lua_pushnumber(L, n);

    // Get the value on top of the stack
    // and set as a global, in this case is the function
    lua_setglobal(L, name);
}

void LuaSetGlobalString(LuaState* L, const char* name, const char* s)
{
    // Push the string
    lua_pushstring(L, s);

    // Get the value on top of the stack
    // and set as a global, in this case is the function
    lua_setglobal(L, name);
}

int LuaLoadModule(LuaState* L, const char* modulePath)
{
    int errorCode = LUA_OK;

	if (!FileExists(modulePath))
	{
		TraceLog(LOG_ERROR, "`init.lua` not found.");
	}

	const char* sourceCodeBody = LoadFileText(modulePath);

	const char* sourceCodeParts[3] = {
		"(function ()",
		sourceCodeBody,
		"end)()"
	};

	const char* sourceCode = TextJoin(sourceCodeParts, 3, "\n");

	UnloadFileText(sourceCodeBody);

	if (errorCode = LuaLoadString(L, sourceCode) != LUA_OK)
	{
        TraceLog(LOG_ERROR, "Unsupported string encoding used for source code.");
	}

	if (
        (errorCode == LUA_OK) &&
        (errorCode = LuaPCall(L, 0, 0, 0) != LUA_OK)
    )
	{
		TraceLog(LOG_ERROR, "Invalid source code.");
	}

	if (errorCode == LUA_OK)
    {
        LuaPop(L, LuaGetTop(L));
    }

	LuaPushInteger(L, errorCode);

	return 1;
}
