// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>

#include "raylib.h"
#include "raylua.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

const char* DIRECTORY_DELIMITER =
#ifdef _WIN32
                            "\\";
#else
                            "/";
#endif

void AbortWithCode(const char* message, int code)
{
	TraceLog(LOG_ERROR, message);

	exit(code);
}

void Abort(const char* message)
{
	AbortWithCode(message, 1);
}

static int Valiant_Abort(LuaState* L)
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

static int Valiant_Exit(LuaState* L)
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

static int Valiant_Log(LuaState* L)
{
	int logLevel = LOG_INFO;

	int messageLoc = 1;

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

static int Valiant_TraceLog(LuaState* L)
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

static const char* ASSETS_SRC_DIR = "." LUA_PATH_SEP "assets" LUA_PATH_SEP "src;" LUA_PATH_DEFAULT;

int main()
{
	const char* cwd = _getcwd(NULL, 0);

	LuaState* L = LuaInit();

	LuaOpenLibs(L);

	LuaSetGlobalInteger(L, "LOG_ALL", LOG_ALL);
	LuaSetGlobalInteger(L, "LOG_DEBUG", LOG_DEBUG);
	LuaSetGlobalInteger(L, "LOG_INFO", LOG_INFO);
	LuaSetGlobalInteger(L, "LOG_ERROR", LOG_ERROR);
	LuaSetGlobalInteger(L, "LOG_FATAL", LOG_FATAL);
	LuaSetGlobalInteger(L, "LOG_TRACE", LOG_TRACE);
	LuaSetGlobalInteger(L, "LOG_WARNING", LOG_WARNING);

	LuaSetGlobalString(L, "CWD", cwd);
	LuaSetGlobalString(L, "DIRECTORY_DELIMITER", DIRECTORY_DELIMITER);

	LuaSetGlobalFunction(L, "Valiant_Abort", Valiant_Abort);
	LuaSetGlobalFunction(L, "Valiant_Exit", Valiant_Exit);
	LuaSetGlobalFunction(L, "Valiant_Log", Valiant_Log);
	LuaSetGlobalFunction(L, "Valiant_TraceLog", Valiant_TraceLog);

	LuaLoadModule(L, "assets/src/valiant.lua");
	LuaLoadModule(L, "assets/src/init.lua");

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(640, 480, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("assets");
	LuaSetGlobalString(L, "LUA_PATH", ASSETS_SRC_DIR);

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	// game loop
	// run the loop until the user presses ESCAPE or presses the Close button on the window
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200, 200, 20, WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	LuaClose(L);

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();

	return 0;
}
