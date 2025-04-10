// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#if !defined(VALIANT__VSTDLIB_H)
#define VALIANT__VSTDLIB_H

#include "raylib.h"
#include "raylua.h"

bool Valiant_isInitialized;

/// <summary>
/// Get the Valiant icon as an image.
/// </summary>
/// <returns>The Valiant icon as an image.</returns>
Image Valiant_GetIconImage(void);

/// <summary>
/// Initialize a new Lua state with Valiant's pre-defined global variables (for use with `LuaInit()`).
/// </summary>
/// <param name="L">The Lua state.</param>
void Valiant_InitStandardLibrary(LuaState* L);

/// <summary>
/// Load all static assets.
/// </summary>
void Valiant_LoadStatic(void);

/// <summary>
/// Unload all static assets.
/// </summary>
void Valiant_UnloadStatic(void);

/// <summary>
/// Abort the application with an error code.
/// </summary>
/// <param name="message">The error message to write.</param>
/// <param name="code">The error code to return.</param>
static void valiant_abortWithCode(const char* message, int code);

/// <summary>
/// Abort the application.
/// </summary>
/// <param name="message">The error message to write.</param>
static void valiant_abort(const char* message);

/// <summary>
/// Abort the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_application_abort(LuaState* L);

/// <summary>
/// Draw the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_draw(LuaState* L);

/// <summary>
/// Exit the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_application_exit(LuaState* L);

/// <summary>
/// Set the target FPS of the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_setTargetFPS(LuaState* L);

/// <summary>
/// Start the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_application_start(LuaState* L);

/// <summary>
/// Stop the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_application_stop(LuaState* L);

/// <summary>
/// Set the assets directory.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_assets_setDirectory(LuaState* L);

/// <summary>
/// Tick the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_tick(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_console_log(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_console_traceLog(LuaState* L);

/// <summary>
/// Begin drawing.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_ui_beginDrawing(LuaState* L);

/// <summary>
/// Draw a solid background color.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_ui_drawBackgroundColor(LuaState* L);

/// <summary>
/// Draw text.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_ui_drawText(LuaState* L);

/// <summary>
/// End drawing.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_ui_endDrawing(LuaState* L);

/// <summary>
/// Close the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_close(LuaState* L);

/// <summary>
/// Open the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_open(LuaState* L);

/// <summary>
/// Return `true` if the window should close; `false` otherwise.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The return count.</returns>
int vstdlib_window_shouldClose(LuaState* L);

#endif // VALIANT__VSTDLIB_H
