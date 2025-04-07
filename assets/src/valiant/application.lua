---Abort the application.
---@param message string The error message to log.
---@param code integer The error code to return.
local function Abort(message, code)
    if type(message) ~= "string" then message = "" end
    if type(code) ~= "number" then code = 1 end
    Valiant_Abort(message, code)
end

---Exit the application.
---@param code integer The error code to return.
local function Exit(code)
    if type(code) ~= "number" then code = 0 end
    Valiant_Exit(code)
end

return {
    Abort = Abort,
    Exit = Exit
}
