local stringutils = require "valiant.core.stringutils"

---Set the language-complexity mode of the Valiant runtime.
---@diagnostic disable-next-line: lowercase-global
function resetglobals()
    _G.Application = require "valiant.core.Application"
    _G.Console = require "valiant.core.Console"
    ---@diagnostic disable-next-line: lowercase-global
    _G.application = Application.create()
    ---@diagnostic disable-next-line: lowercase-global
    _G.console = application.console
end

---Set the language-complexity mode of the Valiant runtime.
---@param name ("advanced"|"simple") The name of the mode.
---@diagnostic disable-next-line: lowercase-global
function setmode(name)
    if name == "advanced" then
        _G.Application = nil
        _G.Console = nil
        _G.application = nil
        _G.console = nil
    elseif name == "simple" then
        resetglobals()
    end
end

---Set the GUI mode of the Valiant runtime.
---@param name ("console"|"window") The name of the mode.
---@diagnostic disable-next-line: lowercase-global
function setuimode(name)
    if name == "console" then
        if _G.window ~= nil then _G.window:close() end
        _G.Window = nil
        _G.window = nil
    elseif name == "window" then
        _G.Color = require "valiant.ui.Color"
        _G.Window = require "valiant.ui.Window"
        _G.window = Window.getInstance()
        _G.window:open()
        while _G.window:isOpen() do
            _G.window:tick()
            _G.window:draw()
        end
    end
end

return {
    resetglobals,
    setmode,
    setuimode
}
