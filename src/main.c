// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>

#include "raylib.h"
#include "raylua.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

void AbortWithCode(const char* message, int code)
{
	TraceLog(LOG_ERROR, message);

	exit(code);
}

void Abort(const char* message)
{
	AbortWithCode(message, 1);
}

static int valiant_application_Abort(LuaState* L)
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
		code = round(LuaCheckNumber(L, codeLoc));
	}

	AbortWithCode(message, code);

	return 0;
}

static int valiant_application_Draw(LuaState* L)
{
	BeginDrawing();
	ClearBackground(PINK);
	DrawText("Hello, Valiant!", 16, 16, 32, SKYBLUE);
	EndDrawing();

	return 0;
}

static int valiant_application_Exit(LuaState* L)
{
	int code = 1;

	int codeLoc = 1;

	if (LuaIsInteger(L, codeLoc))
	{
		code = LuaCheckInteger(L, codeLoc);
	}
	else if (LuaIsNumber(L, codeLoc))
	{
		code = round(LuaCheckNumber(L, codeLoc));
	}

	exit(code);

	return 0;
}

static int valiant_application_Start(LuaState* L)
{
	int configFlags = 0;
	int configFlagsLoc = 1;

	if (LuaIsInteger(L, configFlagsLoc))
	{
		configFlags = LuaCheckInteger(L, configFlagsLoc);
	}

	LuaPushInteger(L, configFlags);

	valiant_window_Open(L);

	while (!WindowShouldClose())
	{
		valiant_application_Tick(L);
		valiant_application_Draw(L);
	}

	valiant_window_Close(L);

	return 0;
}

static int valiant_application_Stop(LuaState* L)
{
	valiant_window_Close(L);
}

static int valiant_application_Tick(LuaState* L)
{
	return 0;
}

static int valiant_console_Log(LuaState* L)
{
	int logLevel = LOG_INFO;

	int messageLoc = 1;

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

static int valiant_console_TraceLog(LuaState* L)
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
		logLevel = round(LuaCheckNumber(L, logLevelLoc));
	}

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

static int valiant_window_Close(LuaState* L)
{
	CloseWindow();
}

static int valiant_window_Open(LuaState* L)
{
	int configFlags = 0;
	int configFlagsLoc = 1;

	if (LuaIsInteger(L, configFlagsLoc))
	{
		configFlags = LuaCheckInteger(L, configFlagsLoc);
	}

	SetConfigFlags(configFlags);

	InitWindow(640, 480, "Valiant");
}

static int valiant_window_ShouldClose(LuaState* L)
{
	lua_pushboolean(L, WindowShouldClose());

	return 1;
}

static const char* ASSETS_SRC_DIR = "." LUA_PATH_SEP "assets" LUA_PATH_SEP "src;" LUA_PATH_DEFAULT;

int main()
{
	LuaState* L = LuaInit();

	LuaLoadModule(L, "assets/src/valiant.lua");
	LuaLoadModule(L, "assets/src/init.lua");

	// // Tell the window to use vsync and work on high DPI displays
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	// SearchAndSetResourceDir("assets");
	// LuaSetGlobalString(L, "LUA_PATH", ASSETS_SRC_DIR);

	// // Load a texture from the resources directory
	// Texture wabbit = LoadTexture("wabbit_alpha.png");

	// // game loop
	// // run the loop until the user presses ESCAPE or presses the Close button on the window
	// while (!WindowShouldClose())
	// {
	// 	// drawing
	// 	BeginDrawing();

	// 	// Setup the back buffer for drawing (clear color and depth buffers)
	// 	ClearBackground(BLACK);

	// 	// draw some text using the default font
	// 	DrawText("Hello Raylib", 200, 200, 20, WHITE);

	// 	// draw our texture to the screen
	// 	DrawTexture(wabbit, 400, 200, WHITE);

	// 	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	// 	EndDrawing();
	// }

	LuaClose(L);

	// // cleanup
	// // unload our texture so it can be cleaned up
	// UnloadTexture(wabbit);

	// // destroy the window and cleanup the OpenGL context
	// CloseWindow();

	return 0;
}
