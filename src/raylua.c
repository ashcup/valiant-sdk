// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

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

int LuaRunString(LuaState* L, const char* sourceCode)
{
    int errorCode = LUA_OK;

    if (errorCode = LuaLoadString(L, sourceCode) != LUA_OK)
	{
        TraceLog(LOG_ERROR, "Invalid source code.");
	}

	if (
        (errorCode == LUA_OK) &&
        (errorCode = LuaPCall(L, 0, 0, 0) != LUA_OK)
    )
	{
        const char* errorMessage = "An unknown error occured.";
        int errorMessageLoc = 1;

        if (LuaIsString(L, errorMessageLoc))
        {
            errorMessage = LuaCheckString(L, errorMessageLoc);
        }

		TraceLog(LOG_ERROR, errorMessage);
	}

	if (errorCode == LUA_OK)
    {
        LuaPop(L, LuaGetTop(L));

        return true;
    }

	return errorCode;
}

int LuaRequire(LuaState* L, const char* modulePath)
{
    // If a module does not exist at `modulePath`:
	if (!FileExists(modulePath))
	{
        // Write to the trace log.
		TraceLog(LOG_ERROR, "`init.lua` not found.");

        // Return an error code.
        return LUA_ERRFILE;
	}

	// const char* sourceCodeBody = LoadFileText(modulePath);
	const char* sourceCode = LoadFileText(modulePath);

    // UnloadFileText(sourceCodeBody);
	int errorCode = LuaRunString(L, sourceCode);

    UnloadFileText(sourceCode);

    return errorCode;
}
