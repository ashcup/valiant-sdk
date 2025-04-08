#include <direct.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "raylua.h"
#include "valiant/vstdlib.h"

void InitValiantStandardLibrary(LuaState* L)
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

void valiant_AbortWithCode(const char* message, int code)
{
	TraceLog(LOG_ERROR, message);

	exit(code);
}

void valiant_Abort(const char* message)
{
	valiant_AbortWithCode(message, 1);
}

int vstdlib_application_Abort(LuaState* L)
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

	valiant_AbortWithCode(message, code);

	return 0;
}

int vstdlib_application_Draw(LuaState* L)
{
	BeginDrawing();
	ClearBackground(PINK);
	DrawText("Hello, Valiant!", 16, 16, 32, SKYBLUE);
	EndDrawing();

	return 0;
}

int vstdlib_application_Exit(LuaState* L)
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

int vstdlib_application_SetTargetFPS(LuaState* L)
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

int vstdlib_application_Start(LuaState* L)
{
	int configFlags = 0;
	int configFlagsLoc = 1;

	if (LuaIsInteger(L, configFlagsLoc))
	{
		configFlags = LuaCheckInteger(L, configFlagsLoc);
	}

	LuaPushInteger(L, configFlags);

	vstdlib_window_Open(L);

	while (!WindowShouldClose())
	{
		vstdlib_application_Tick(L);
		vstdlib_application_Draw(L);
	}

	vstdlib_window_Close(L);

	return 0;
}

int vstdlib_application_Stop(LuaState* L)
{
	vstdlib_window_Close(L);

	return 0;
}

int vstdlib_application_Tick(LuaState* L)
{
	return 0;
}

int vstdlib_console_Log(LuaState* L)
{
	int logLevel = LOG_INFO;

	int messageLoc = 1;

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

int vstdlib_console_TraceLog(LuaState* L)
{
	int logLevel = 1;

	int logLevelLoc = 1;
	int messageLoc = 2;

	if (LuaIsInteger(L, logLevelLoc))
	{
		logLevel = LuaCheckInteger(L, logLevelLoc);
	}
	else if (LuaIsNumber(L, logLevelLoc))
	{
		logLevel = (int)round(LuaCheckNumber(L, logLevelLoc));
	}

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

int vstdlib_window_Close(LuaState* L)
{
	CloseWindow();

	return 0;
}

int vstdlib_window_Open(LuaState* L)
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

int vstdlib_window_ShouldClose(LuaState* L)
{
	lua_pushboolean(L, WindowShouldClose());

	return 1;
}
