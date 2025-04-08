// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>

#include "raylib.h"
#include "raylua.h"
#include "valiant/core.h"
#include "valiant/runtime.h"
#include "valiant/vstdlib.h"

LuaState* InitValiant(void)
{
	LuaState* L = LuaInit();

	LuaOpenLibs(L);

	InitValiantGlobals(L);

	LuaLoadModule(L, "assets/src/valiant.lua");
	LuaLoadModule(L, "assets/src/init.lua");

	return L;
}

void InitValiantGlobals(LuaState* L)
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

	LuaSetGlobalCFunction(L, "vstdlib_application_Abort", vstdlib_application_Abort);
	LuaSetGlobalCFunction(L, "vstdlib_application_Draw", vstdlib_application_Draw);
	LuaSetGlobalCFunction(L, "vstdlib_application_Exit", vstdlib_application_Exit);
	LuaSetGlobalCFunction(L, "vstdlib_application_SetTargetFPS", vstdlib_application_SetTargetFPS);
	LuaSetGlobalCFunction(L, "vstdlib_application_Start", vstdlib_application_Start);
	LuaSetGlobalCFunction(L, "vstdlib_application_Stop", vstdlib_application_Stop);
	LuaSetGlobalCFunction(L, "vstdlib_application_Tick", vstdlib_application_Tick);
	LuaSetGlobalCFunction(L, "vstdlib_console_Log", vstdlib_console_Log);
	LuaSetGlobalCFunction(L, "vstdlib_console_TraceLog", vstdlib_console_TraceLog);
	LuaSetGlobalCFunction(L, "vstdlib_window_Close", vstdlib_window_Close);
	LuaSetGlobalCFunction(L, "vstdlib_window_Open", vstdlib_window_Open);
	LuaSetGlobalCFunction(L, "vstdlib_window_ShouldClose", vstdlib_window_ShouldClose);

    static const char* ASSETS_SRC_DIR = "." LUA_PATH_SEP "assets" LUA_PATH_SEP "src;" LUA_PATH_DEFAULT;
}
