
function LuaAppendPath(pathBase)
    package.path = pathBase .. "?.lua" .. ";" .. package.path
    package.path = pathBase .. "?" .. DIRECTORY_DELIMITER .. "init.lua" .. ";" .. package.path
end

local pathBase = CWD .. DIRECTORY_DELIMITER .. "assets" .. DIRECTORY_DELIMITER .. "src" .. DIRECTORY_DELIMITER;

LuaAppendPath(pathBase)
