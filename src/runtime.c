// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <direct.h>

#include "raylib.h"
#include "raylua.h"
#include "valiant/core.h"
#include "valiant/runtime.h"
#include "valiant/vstdlib.h"

LuaState* InitValiant(void)
{
	LuaState* L = LuaInit();

	LuaOpenLibs(L);

	InitValiantStandardLibrary(L);

	LuaLoadModule(L, "assets/src/valiant.lua");
	LuaLoadModule(L, "assets/src/init.lua");

	return L;
}
