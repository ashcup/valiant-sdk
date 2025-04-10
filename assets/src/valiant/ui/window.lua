-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

-- local raylib = require "raylib"
-- local events = require "valiant.core.events"

local Window = class {
    width = 640,
    height = 480,
    title = "Valiant"
}

function Window:__init() end

function Window:__gc()
    self:close()
end

---Stop the window.
function Window:close()
    vstdlib_window_close()
end

---Draw the application.
function Window:draw()
    vstdlib_ui_beginDrawing()
    -- vstdlib_ui_drawBackgroundColor(PINK)
    -- vstdlib_ui_drawText("Hello, Valiant!", 16, 24, 32, SKYBLUE)
    -- events.EventSystem.getInstance().emit "draw"
    vstdlib_ui_endDrawing()
end

---Returns `true` if the window is open; `false` otherwise.
---@return boolean isOpen Whether or not the window is open.
function Window:isOpen()
    return not self:shouldClose()
end

function Window:setTargetFPS(targetFPS)
    if type(targetFPS) ~= "number" then targetFPS = 60 end
    vstdlib_window_setTargetFPS(targetFPS)
end

function Window:shouldClose()
    return vstdlib_window_shouldClose()
end

---Start the window.
---@param flags integer The flags to pass to the window.
function Window:open(flags)
    vstdlib_window_open(flags)
end

---Tick the application.
function Window:tick()
    vstdlib_window_tick()
end

local singleton = Window.create()

function Window.getInstance()
    return singleton
end

return Window
