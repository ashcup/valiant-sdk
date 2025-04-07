---Abort the application.
---@param message string The error message to log.
---@param code integer The error code to return.
local function Abort(message, code)
    if type(message) ~= "string" then message = "" end
    if type(code) ~= "number" then code = 1 end
    valiant_application_Abort(message, code)
end

---Draw the application.
local function Draw()
    valiant_application_Draw()
end

---Exit the application.
---@param code integer The error code to return.
local function Exit(code)
    if type(code) ~= "number" then code = 0 end
    valiant_application_Exit(code)
end

---Start the application.
local function Start(flags)
    valiant_application_Start(flags)
end

---Stop the application.
local function Stop()
    valiant_application_Stop()
end

---Tick the application.
local function Tick()
    valiant_application_Tick()
end

return {
    Abort = Abort,
    Draw = Draw,
    Exit = Exit,
    Start = Start,
    Stop = Stop,
    Tick = Tick
}
