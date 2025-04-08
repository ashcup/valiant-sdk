-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

---Start the window.
local function Start()
    vstdlib_window_Start()
end

---Stop the window.
local function Stop()
    vstdlib_window_Start()
end

return {
    Start = Start,
    Stop = Stop
}
