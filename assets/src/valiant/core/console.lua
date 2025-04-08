-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local function Log(message)
    if type(message) ~= "string" then message = "" end
    vstdlib_console_Log(message)
end

local function TraceLog(logLevel, message)
    if type(logLevel) ~= "number" then logLevel = LOG_INFO end
    if type(message) ~= "string" then message = "" end
    vstdlib_console_TraceLog(logLevel, message)
end

return {
    Log = Log,
    TraceLog = TraceLog
}
