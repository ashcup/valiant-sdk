// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

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

static int Valiant_Core_Abort(LuaState* L)
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

static int Valiant_Core_Exit(LuaState* L)
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

static int Valiant_Core_Log(LuaState* L)
{
	int logLevel = LOG_INFO;

	int messageLoc = 1;

	const char* message = LuaCheckString(L, messageLoc);

	TraceLog(logLevel, message);

	return 0;
}

static int Valiant_Core_TraceLog(LuaState* L)
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

int main()
{
	LuaState* L = LuaInit();

	LuaOpenLibs(L);

	const char* modulePath = "assets/src/init.lua";

	if (!FileExists(modulePath))
	{
		Abort("`init.lua` not found.");
	}

	LuaSetGlobalFunction(L, "Abort", Valiant_Core_Abort);
	LuaSetGlobalFunction(L, "Exit", Valiant_Core_Exit);
	LuaSetGlobalFunction(L, "Log", Valiant_Core_Log);
	LuaSetGlobalFunction(L, "TraceLog", Valiant_Core_TraceLog);

	const char* sourceCode = LoadFileText(modulePath);

	if (LuaLoadString(L, sourceCode) != LUA_OK)
	{
		Abort("Unsupported string encoding used for source code.");
	}

	if (LuaPCall(L, 0, 0, 0) != LUA_OK)
	{
		Abort("Invalid source code.");
	}

	LuaPop(L, LuaGetTop(L));

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(640, 480, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

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
