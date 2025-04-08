-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

---Abort the application.
---@param message string The error message to log.
---@param code integer The error code to return.
local function Abort(message, code)
    if type(message) ~= "string" then message = "" end
    if type(code) ~= "number" then code = 1 end
    vstdlib_application_Abort(message, code)
end

---Draw the application.
local function Draw()
    vstdlib_application_Draw()
end

---Exit the application.
---@param code integer The error code to return.
local function Exit(code)
    if type(code) ~= "number" then code = 0 end
    vstdlib_application_Exit(code)
end

local function SetTargetFPS(targetFPS)
    if type(targetFPS) ~= "number" then targetFPS = 60 end
    vstdlib_application_SetTargetFPS(targetFPS)
end

---Start the application.
local function Start(flags)
    vstdlib_application_Start(flags)
end

---Stop the application.
local function Stop()
    vstdlib_application_Stop()
end

---Tick the application.
local function Tick()
    vstdlib_application_Tick()
end

return {
    Abort = Abort,
    Draw = Draw,
    Exit = Exit,
    SetTargetFPS = SetTargetFPS,
    Start = Start,
    Stop = Stop,
    Tick = Tick
}
