-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local Console = class {
    logLevel = LOG_INFO
}

function Console:log(message)
    vstdlib_console_log(message)
end

return Console
