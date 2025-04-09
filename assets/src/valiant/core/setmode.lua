---Set the language-complexity mode of the Valiant runtime.
---@param name ("advanced"|"simple") The name of the mode.
---@diagnostic disable-next-line: lowercase-global
function setmode(name)
    if name == "advanced" then
        _G.Console = nil
        _G.console = nil
    elseif name == "simple" then
        _G.Application = require "valiant.core.Application"
        _G.Console = require "valiant.core.Console"
        ---@diagnostic disable-next-line: lowercase-global
        _G.application = Application.create()
        ---@diagnostic disable-next-line: lowercase-global
        _G.console = application.console
    end
end

return setmode
