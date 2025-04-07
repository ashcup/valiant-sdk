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

static const char* DIRECTORY_DELIMITER =
#ifdef _WIN32
"\\";
#else
"/";
#endif

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
#define LuaInitPro()                            luaL_newstate()
#define LuaIsInteger(L, n)                      lua_isinteger(L, n)
#define LuaIsNumber(L, n)                       lua_isnumber(L, n)
#define LuaIsString(L, n)                       lua_isstring(L, n)
#define LuaLoadString(L, s)                     luaL_loadstring(L, s)
#define LuaOpenLibs(L)                          luaL_openlibs(L)
#define LuaPCall(L, n, r, f)                    lua_pcall(L, n, r, f)
#define LuaPop(L, n)                            lua_pop(L, n)
#define LuaPushBoolean(L, b)                    lua_pushboolean(L, b)
#define LuaPushCFunction(L, f)                  lua_pushcfunction(L, f)
#define LuaPushInteger(L, n)                    lua_pushinteger(L, n)
#define LuaPushNumber(L, n)                     lua_pushnumber(L, n)
#define LuaPushString(L, s)                     lua_pushstring(L, s)

/// <summary>
/// Abort the application with an error code.
/// </summary>
/// <param name="message">The error message to write.</param>
/// <param name="code">The error code to return.</param>
static void AbortWithCode(const char* message, int code);

/// <summary>
/// Abort the application.
/// </summary>
/// <param name="message">The error message to write.</param>
static void Abort(const char* message);

/// <summary>
/// Abort the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Abort(LuaState* L);

/// <summary>
/// Draw the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Draw(LuaState* L);

/// <summary>
/// Exit the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Exit(LuaState* L);

/// <summary>
/// Start the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Start(LuaState* L);

/// <summary>
/// Stop the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Stop(LuaState* L);

/// <summary>
/// Tick the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_application_Tick(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_console_Log(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_console_TraceLog(LuaState* L);

/// <summary>
/// Close the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_window_Close(LuaState* L);

/// <summary>
/// Open the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_window_Open(LuaState* L);

/// <summary>
/// Return `true` if the window should close; `false` otherwise.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
static int valiant_window_ShouldClose(LuaState* L);

/// <summary>
/// Initialize a new raylua state.
/// </summary>
/// <returns>A new raylua state.</returns>
LuaState* LuaInit();

/// <summary>
/// Initialize a new Lua state with raylua globals (for use with `LuaInitPro()`).
/// </summary>
/// <param name="L">The Lua state.</param>
void LuaInitGlobals(LuaState* L);

/// <summary>
/// Load a Lua module.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="modulePath"></param>
/// <returns></returns>
int LuaLoadModule(LuaState* L, const char* modulePath);

/// <summary>
/// Set a global variable.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="name">The name of the global variable.</param>
/// <param name="f">The new value of the global variable.</param>
void LuaSetGlobalCFunction(LuaState* L, const char* name, LuaCFunction f);

/// <summary>
/// Set a global variable.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="name">The name of the global variable.</param>
/// <param name="n">The new value of the global variable.</param>
void LuaSetGlobalInteger(LuaState* L, const char* name, int n);

/// <summary>
/// Set a global variable.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="name">The name of the global variable.</param>
/// <param name="n">The new value of the global variable.</param>
void LuaSetGlobalNumber(LuaState* L, const char* name, double n);

/// <summary>
/// Set a global variable.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <param name="name">The name of the global variable.</param>
/// <param name="s">The new value of the global variable.</param>
void LuaSetGlobalString(LuaState* L, const char* name, const char* s);

LuaState* LuaInit()
{
	LuaState* L = LuaInitPro();

	LuaOpenLibs(L);

	LuaInitGlobals(L);

	return L;
}

void LuaInitGlobals(LuaState* L)
{
	const char* cwd = _getcwd(NULL, 0);

	LuaSetGlobalInteger(L, "FLAG_VSYNC_HINT", FLAG_VSYNC_HINT);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI);
	LuaSetGlobalInteger(L, "LOG_ALL", LOG_ALL);
	LuaSetGlobalInteger(L, "LOG_DEBUG", LOG_DEBUG);
	LuaSetGlobalInteger(L, "LOG_INFO", LOG_INFO);
	LuaSetGlobalInteger(L, "LOG_ERROR", LOG_ERROR);
	LuaSetGlobalInteger(L, "LOG_FATAL", LOG_FATAL);
	LuaSetGlobalInteger(L, "LOG_TRACE", LOG_TRACE);
	LuaSetGlobalInteger(L, "LOG_WARNING", LOG_WARNING);

	LuaSetGlobalString(L, "CWD", cwd);
	LuaSetGlobalString(L, "DIRECTORY_DELIMITER", DIRECTORY_DELIMITER);

	LuaSetGlobalCFunction(L, "valiant_application_Abort", valiant_application_Abort);
	LuaSetGlobalCFunction(L, "valiant_application_Draw", valiant_application_Draw);
	LuaSetGlobalCFunction(L, "valiant_application_Exit", valiant_application_Exit);
	LuaSetGlobalCFunction(L, "valiant_application_Start", valiant_application_Start);
	LuaSetGlobalCFunction(L, "valiant_application_Stop", valiant_application_Stop);
	LuaSetGlobalCFunction(L, "valiant_application_Tick", valiant_application_Tick);
	LuaSetGlobalCFunction(L, "valiant_console_Log", valiant_console_Log);
	LuaSetGlobalCFunction(L, "valiant_console_TraceLog", valiant_console_TraceLog);
	LuaSetGlobalCFunction(L, "valiant_window_Close", valiant_window_Close);
	LuaSetGlobalCFunction(L, "valiant_window_Open", valiant_window_Open);
	LuaSetGlobalCFunction(L, "valiant_window_ShouldClose", valiant_window_ShouldClose);
}

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

#endif // RAYLUA_H
