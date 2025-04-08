#include "raylua.h"

/// <summary>
/// Initialize a new Lua state with Valiant's pre-defined global variables (for use with `LuaInit()`).
/// </summary>
/// <param name="L">The Lua state.</param>
void InitValiantStandardLibrary(LuaState* L);

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
