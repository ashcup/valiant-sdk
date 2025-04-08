#include "raylua.h"

/// <summary>
/// Initialize a new Lua state with Valiant's pre-defined global variables (for use with `LuaInit()`).
/// </summary>
/// <param name="L">The Lua state.</param>
void InitValiantStandardLibrary(LuaState* L);

/// <summary>
/// valiant_Abort the application with an error code.
/// </summary>
/// <param name="message">The error message to write.</param>
/// <param name="code">The error code to return.</param>
static void valiant_AbortWithCode(const char* message, int code);

/// <summary>
/// valiant_Abort the application.
/// </summary>
/// <param name="message">The error message to write.</param>
static void valiant_Abort(const char* message);

/// <summary>
/// valiant_Abort the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Abort(LuaState* L);

/// <summary>
/// Draw the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Draw(LuaState* L);

/// <summary>
/// Exit the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Exit(LuaState* L);

/// <summary>
/// Set the target FPS of the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_SetTargetFPS(LuaState* L);

/// <summary>
/// Start the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Start(LuaState* L);

/// <summary>
/// Stop the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Stop(LuaState* L);

/// <summary>
/// Tick the application.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_application_Tick(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_console_Log(LuaState* L);

/// <summary>
/// Write a message to the trace log.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_console_TraceLog(LuaState* L);

/// <summary>
/// Close the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_window_Close(LuaState* L);

/// <summary>
/// Open the window.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_window_Open(LuaState* L);

/// <summary>
/// Return `true` if the window should close; `false` otherwise.
/// </summary>
/// <param name="L">The Lua state.</param>
/// <returns>The number of returned values.</returns>
int vstdlib_window_ShouldClose(LuaState* L);
