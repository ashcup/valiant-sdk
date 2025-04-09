---Set the language-complexity mode of the Valiant runtime.
---@param name ("advanced"|"simple") The name of the mode.
---@diagnostic disable-next-line: lowercase-global
function setmode(name)
    if name == "advanced" then
        _G.Console = nil
        _G.console = nil
    elseif name == "simple" then
        Application = require "valiant.core.Application"
        Console = require "valiant.core.Console"
        ---@diagnostic disable-next-line: lowercase-global
        application = Application.create()
        ---@diagnostic disable-next-line: lowercase-global
        console = application.console
    end
end

return setmode
