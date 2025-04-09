-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local Console = require "valiant.core.Console"

local Application = class {
    __extends = { Console }
}

---Abort the application.
---@param message string The error message to log.
---@param code integer The error code to return.
function Application:abort(message, code)
    if type(message) ~= "string" then message = "" end
    if type(code) ~= "number" then code = 1 end
    vstdlib_application_abort(message, code)
end

---Exit the application.
---@param code integer The error code to return.
function Application:exit(code)
    if type(code) ~= "number" then code = 0 end
    vstdlib_application_exit(code)
end

---Start the application.
function Application:start()
    vstdlib_application_start()
end

---Stop the application.
function Application:stop()
    vstdlib_application_stop()
end

local singleton = Application.create()

return singleton
