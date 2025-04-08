#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "raylua.h"
#include "valiant/vstdlib.h"

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
