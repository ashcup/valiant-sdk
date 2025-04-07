// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#if !defined(RAYLUA_H)
#define RAYLUA_H

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef lua_Alloc LuaAlloc;
typedef lua_CFunction LuaCFunction;
typedef lua_Debug LuaDebug;
typedef lua_Hook LuaHook;
typedef lua_Integer LuaInteger;
typedef lua_KContext LuaKContext;
typedef lua_KFunction LuaKFunction;
typedef lua_State LuaState;
typedef lua_Writer LuaWriter;

#define LuaAbsIndex(L, idx)                     lua_absindex(L, idx)
#define LuaArith(L, op)                         lua_arith(L, op)
#define LuaAtPanic(L, panicf)                   lua_atpanic(L, panicf)
#define LuaCall(L, n, r)                        lua_call(L, n, r)
#define LuaCallK(L, nargs, nresults, ctx, k)    lua_callk(L, nargs, nresults, ctx, k)
#define LuaCheckStack(L, n)                     lua_checkstack(L, n)
#define LuaCheckInteger(L, n)                   luaL_checkinteger(L, n)
#define LuaCheckNumber(L, n)                    luaL_checknumber(L, n)
#define LuaCheckString(L, n)                    luaL_checkstring(L, n)
#define LuaClose(L)                             lua_close(L)
#define LuaCloseSlot(L, idx)                    lua_closeslot(L, idx)
#define LuaCloseThread(L, from)                 lua_closethread(L, from)
#define LuaCompare(L, idx1, idx2, op)           lua_compare(L, idx1, idx2, op)
#define LuaConcat(L, n)                         lua_concat(L, n)
#define LuaCopy(L, fromidx, toidx)              lua_copy(L, fromidx, toidx)
#define LuaCreateTable(L, narr, nrec)           lua_createtable(L, narr, nrec)
#define LuaDump(L, writer, data, strip)         lua_dump(L, writer, data, strip)
#define LuaError(L)                             lua_error(L)
#define LuaGC(L, what, ...)                     lua_gc(L, what, ...)
#define LuaGetAllocF(L, ud)                     lua_getallocf(L, ud)
#define LuaGetExtraSpace(L)                     lua_getextraspace(((void*)((char*)(L) - LUA_EXTRASPACE))
#define LuaGetField(L, idx, k)                  lua_getfield(L, idx, k)
#define LuaGetGlobal(L, name)                   lua_getglobal(L, name)
#define LuaGetHook(L)                           lua_gethook(L)
#define LuaGetHookCount(L)                      lua_gethookcount(L)
#define LuaGetHookMask(L)                       lua_gethookmask(L)
#define LuaGetI(L, idx, n)                      lua_geti(L, idx, n)
#define LuaGetInfo(L, what, ar)                 lua_getinfo(L, what, ar)
#define LuaGetIUserValue(L, idx, n)             lua_getiuservalue(L, idx, n)
#define LuaGetTop(L)                            lua_gettop(L)
#define LuaInit()                               luaL_newstate()
#define LuaIsInteger(L, n)                      lua_isinteger(L, n)
#define LuaIsNumber(L, n)                       lua_isnumber(L, n)
#define LuaIsString(L, n)                       lua_isstring(L, n)
#define LuaLoadString(L, s)                     luaL_loadstring(L, s)
#define LuaOpenLibs(L)                          luaL_openlibs(L)
#define LuaPCall(L, n, r, f)                    lua_pcall(L, n, r, f)
#define LuaPop(L, n)                            lua_pop(L, n)

void LuaSetGlobalFunction(LuaState* L, const char* name, LuaCFunction f);
void LuaSetGlobalInteger(LuaState* L, const char* name, int i);

void LuaSetGlobalFunction(LuaState* L, const char* name, LuaCFunction f)
{
    // Push the pointer to function
    lua_pushcfunction(L, f);

    // Get the value on top of the stack
    // and set as a global, in this case is the function
    lua_setglobal(L, name);
}

void LuaSetGlobalInteger(LuaState* L, const char* name, int i)
{
    // Push the integer
    lua_pushinteger(L, i);

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

    const char* sourceCode = LoadFileText(modulePath);

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

    UnloadFileText(sourceCode);

    return errorCode;
}

#endif // RAYLUA_H
