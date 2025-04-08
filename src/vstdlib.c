// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "raylua.h"
#include "resource_dir.h"
#include "valiant/vstdlib.h"

static void _InitConstants(LuaState* L);
static void _InitConstants_Integers(LuaState* L);
static void _InitConstants_Integers_LogFlags(LuaState* L);
static void _InitConstants_Integers_WindowFlags(LuaState* L);
static void _InitConstants_Strings(LuaState* L);
static void _InitFunctions(LuaState* L);

void InitValiantStandardLibrary(LuaState* L)
{
	_InitConstants(L);
	_InitFunctions(L);
}

static void _InitConstants(LuaState* L)
{
	_InitConstants_Integers(L);
	_InitConstants_Strings(L);
}

static void _InitConstants_Integers(LuaState* L)
{
	_InitConstants_Integers_LogFlags(L);
	_InitConstants_Integers_WindowFlags(L);
}

static void _InitConstants_Integers_LogFlags(LuaState* L)
{
	_InitConstants_Integers_WindowFlags(L);
	LuaSetGlobalInteger(L, "LOG_ALL", LOG_ALL);
	LuaSetGlobalInteger(L, "LOG_DEBUG", LOG_DEBUG);
	LuaSetGlobalInteger(L, "LOG_INFO", LOG_INFO);
	LuaSetGlobalInteger(L, "LOG_ERROR", LOG_ERROR);
	LuaSetGlobalInteger(L, "LOG_FATAL", LOG_FATAL);
	LuaSetGlobalInteger(L, "LOG_TRACE", LOG_TRACE);
	LuaSetGlobalInteger(L, "LOG_WARNING", LOG_WARNING);
}

static void _InitConstants_Integers_WindowFlags(LuaState* L)
{
	LuaSetGlobalInteger(L, "FLAG_BORDERLESS_WINDOWED_MODE", FLAG_BORDERLESS_WINDOWED_MODE);
	LuaSetGlobalInteger(L, "FLAG_FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE);
	LuaSetGlobalInteger(L, "FLAG_INTERLACED_HINT", FLAG_INTERLACED_HINT);
	LuaSetGlobalInteger(L, "FLAG_MSAA_4X_HINT", FLAG_MSAA_4X_HINT);
	LuaSetGlobalInteger(L, "FLAG_VSYNC_HINT", FLAG_VSYNC_HINT);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_MAXIMIZED", FLAG_WINDOW_MAXIMIZED);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_MINIMIZED", FLAG_WINDOW_MINIMIZED);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_MOUSE_PASSTHROUGH", FLAG_WINDOW_MOUSE_PASSTHROUGH);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_TOPMOST", FLAG_WINDOW_TOPMOST);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED);
	LuaSetGlobalInteger(L, "FLAG_WINDOW_UNFOCUSED", FLAG_WINDOW_UNFOCUSED);
}

static void _InitConstants_Strings(LuaState* L)
{
	const char* cwd = _getcwd(NULL, 0);

	LuaSetGlobalString(L, "CWD", cwd);
	LuaSetGlobalString(L, "DIRECTORY_DELIMITER", DIRECTORY_DELIMITER);
}

static void _InitFunctions(LuaState* L)
{
	LuaSetGlobalCFunction(L, "vstdlib_application_abort", vstdlib_application_abort);
	LuaSetGlobalCFunction(L, "vstdlib_window_draw", vstdlib_window_draw);
	LuaSetGlobalCFunction(L, "vstdlib_application_exit", vstdlib_application_exit);
	LuaSetGlobalCFunction(L, "vstdlib_assets_setDirectory", vstdlib_assets_setDirectory);
	LuaSetGlobalCFunction(L, "vstdlib_window_setTargetFPS", vstdlib_window_setTargetFPS);
	LuaSetGlobalCFunction(L, "vstdlib_application_start", vstdlib_application_start);
	LuaSetGlobalCFunction(L, "vstdlib_application_stop", vstdlib_application_stop);
	LuaSetGlobalCFunction(L, "vstdlib_window_tick", vstdlib_window_tick);
	LuaSetGlobalCFunction(L, "vstdlib_console_log", vstdlib_console_log);
	LuaSetGlobalCFunction(L, "vstdlib_console_traceLog", vstdlib_console_traceLog);
	LuaSetGlobalCFunction(L, "vstdlib_ui_beginDrawing", vstdlib_ui_beginDrawing);
	LuaSetGlobalCFunction(L, "vstdlib_ui_endDrawing", vstdlib_ui_endDrawing);
	LuaSetGlobalCFunction(L, "vstdlib_window_close", vstdlib_window_close);
	LuaSetGlobalCFunction(L, "vstdlib_window_open", vstdlib_window_open);
	LuaSetGlobalCFunction(L, "vstdlib_window_shouldClose", vstdlib_window_shouldClose);
}

void valiant_abortWithCode(const char* message, int code)
{
	TraceLog(LOG_ERROR, message);

	exit(code);
}

void valiant_abort(const char* message)
{
	valiant_abortWithCode(message, 1);
}

int vstdlib_application_abort(LuaState* L)
{
	const char* message = LuaCheckString(L, 1);
	int code = 1;

	int codeLoc = 2;

	if (LuaIsInteger(L, codeLoc))
	{
		code = LuaCheckInteger(L, codeLoc);
	}
	else if (LuaIsNumber(L, codeLoc))
	{
		code = (int)round(LuaCheckNumber(L, codeLoc));
	}

	valiant_abortWithCode(message, code);

	return 0;
}

int vstdlib_window_draw(LuaState* L)
{
	BeginDrawing();
	ClearBackground(PINK);
	DrawText("Hello, Valiant!", 16, 16, 32, SKYBLUE);
	EndDrawing();

	return 0;
}

int vstdlib_application_exit(LuaState* L)
{
	int code = 1;

	int codeLoc = 1;

	if (LuaIsInteger(L, codeLoc))
	{
		code = LuaCheckInteger(L, codeLoc);
	}
	else if (LuaIsNumber(L, codeLoc))
	{
		code = (int)round(LuaCheckNumber(L, codeLoc));
	}

	exit(code);

	return 0;
}

int vstdlib_application_start(LuaState* L)
{
	int configFlags = 0;
	int configFlagsLoc = 1;

	if (LuaIsInteger(L, configFlagsLoc))
	{
		configFlags = LuaCheckInteger(L, configFlagsLoc);
	}

	LuaPushInteger(L, configFlags);

	vstdlib_window_open(L);

	while (!WindowShouldClose())
	{
		vstdlib_window_tick(L);
		vstdlib_window_draw(L);
	}

	vstdlib_window_close(L);

	return 0;
}

int vstdlib_application_stop(LuaState* L)
{
	vstdlib_window_close(L);

	return 0;
}

int vstdlib_assets_setDirectory(LuaState* L)
{
	const char* directoryPath = LuaCheckString(L, 1);

	SearchAndSetResourceDir(directoryPath);
}

int vstdlib_window_tick(LuaState* L)
{
	return 0;
}

int vstdlib_console_log(LuaState* L)
{
	int logLevel = LOG_INFO;

	int messageLoc = 1;

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

int vstdlib_console_traceLog(LuaState* L)
{
	int logLevel = 1;

	int messageLoc = 1;
	int logLevelLoc = 2;

	const char* message = LuaCheckString(L, messageLoc);

	if (LuaIsInteger(L, logLevelLoc))
	{
		logLevel = LuaCheckInteger(L, logLevelLoc);
	}
	else if (LuaIsNumber(L, logLevelLoc))
	{
		logLevel = (int)round(LuaCheckNumber(L, logLevelLoc));
	}

	TraceLog(logLevel, message);

	return 0;
}

int vstdlib_ui_beginDrawing(LuaState* L)
{
	BeginDrawing();

	return 0;
}

int vstdlib_ui_endDrawing(LuaState* L)
{
	EndDrawing();

	return 0;
}

int vstdlib_window_close(LuaState* L)
{
	CloseWindow();

	return 0;
}

int vstdlib_window_open(LuaState* L)
{
	int configFlags = 0;
	int configFlagsLoc = 1;

	if (LuaIsInteger(L, configFlagsLoc))
	{
		configFlags = LuaCheckInteger(L, configFlagsLoc);
	}

	SetConfigFlags(configFlags);

	InitWindow(640, 480, "Valiant");

	return 0;
}

int vstdlib_window_setTargetFPS(LuaState* L)
{
	int targetFPS = 60;

	int targetFPSLoc = 1;

	if (LuaIsInteger(L, targetFPSLoc))
	{
		targetFPS = LuaCheckInteger(L, targetFPSLoc);
	}
	else if (LuaIsNumber(L, targetFPSLoc))
	{
		targetFPS = (int)round(LuaCheckNumber(L, targetFPSLoc));
	}

	SetTargetFPS(targetFPS);
}

int vstdlib_window_shouldClose(LuaState* L)
{
	lua_pushboolean(L, WindowShouldClose());

	return 1;
}
