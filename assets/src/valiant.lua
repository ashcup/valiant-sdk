-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

function LuaAppendPath(pathBase)
    package.path = pathBase .. "?.lua" .. ";" .. package.path
    package.path = pathBase .. "?" .. DIRECTORY_DELIMITER .. "init.lua" .. ";" .. package.path
end

local pathBase = CWD .. DIRECTORY_DELIMITER .. "assets" .. DIRECTORY_DELIMITER .. "src" .. DIRECTORY_DELIMITER;

LuaAppendPath(pathBase)
