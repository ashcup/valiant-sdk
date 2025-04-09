---Set the language-complexity mode of the Valiant runtime.
---@param name ("advanced"|"simple") The name of the mode.
---@diagnostic disable-next-line: lowercase-global
function setmode(name)
    if name == "advanced" then
        _G.Console = nil
        _G.console = nil
    elseif name == "simple" then
        Console = require "valiant.core.console"
        ---@diagnostic disable-next-line: lowercase-global
        console = Console.create()
    end
end

return setmode
