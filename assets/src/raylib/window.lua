-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local window = {}

---Close the window.
function window.close()
    vstdlib_window_close()
end

---Initialize the window.
---@param width integer The width of the window.
---@param height integer The height of the window.
---@param title string The title of the window.
function window.init(width, height, title)
    vstdlib_window_init(width, height, title)
end

return window
