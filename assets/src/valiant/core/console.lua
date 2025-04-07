local function Log(message)
    if type(message) ~= "string" then message = "" end
    valiant_console_Log(message)
end

local function TraceLog(logLevel, message)
    if type(logLevel) ~= "number" then logLevel = LOG_INFO end
    if type(message) ~= "string" then message = "" end
    valiant_console_TraceLog(logLevel, message)
end

return {
    Log = Log,
    TraceLog = TraceLog
}
