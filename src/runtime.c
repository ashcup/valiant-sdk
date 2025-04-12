// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>

#include "raylib.h"
#include "raylua.h"
#include "valiant/core.h"
#include "valiant/runtime.h"
#include "valiant/vstdlib.h"

LuaState* valiant_Init(void)
{
	if (!valiant_isInitialized)
	{
		valiant_LoadStatic();
	}

	LuaState* L = LuaInit();

	LuaOpenLibs(L);

	valiant_InitStandardLibrary(L);

	LuaRequire(L, "assets/src/valiant.lua");
	LuaRequire(L, "assets/src/init.lua");

	valiant_instanceCount++;

	return L;
}

void valiant_Close(LuaState* L)
{
	// Subtract 1 from the instance count and check if any remain:
	if (valiant_instanceCount-- < 1)
	{
		valiant_UnloadStatic();
	}
}
