-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local function valiant__LuaAppendPath(pathBase)
    package.path = pathBase .. "?.lua" .. ";" .. package.path
    package.path = pathBase .. "?" .. DIRECTORY_DELIMITER .. "init.lua" .. ";" .. package.path
end

local valiant__pathBase = CWD .. DIRECTORY_DELIMITER .. "assets" .. DIRECTORY_DELIMITER .. "src" .. DIRECTORY_DELIMITER;

valiant__LuaAppendPath(valiant__pathBase)

local valiant__oop = require "valiant.core.oop"

---@diagnostic disable-next-line: lowercase-global
class = valiant__oop.class

---@diagnostic disable-next-line: lowercase-global
instanceof = valiant__oop.instanceof

require "valiant.core.mode"

-- Enable simple mode.
-- NOTE: Some runtime environment initialization may be placed beneath here to reduce time spent developing and debugging the runtime environment initialization. However, no globalvars should ever be defined beneath here.

setmode "simple"
