// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "raylib.h"
#include "raylua.h"
#include "valiant/core.h"
#include "valiant/runtime.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main()
{
	LuaState* L = InitValiant();

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
