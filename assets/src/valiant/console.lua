local function Log(message)
    if type(message) ~= "string" then message = "" end
    Valiant_Log(message)
end

local function TraceLog(logLevel, message)
    if type(logLevel) ~= "number" then logLevel = LOG_INFO end
    if type(message) ~= "string" then message = "" end
    Valiant_TraceLog(logLevel, message)
end

return {
    Log = Log,
    TraceLog = TraceLog
}
