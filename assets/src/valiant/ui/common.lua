-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local common = {}

function common.startDrawing()
    vstdlib_ui_beginDrawing()
end

function common.stopDrawing()
    vstdlib_ui_endDrawing()
end

return common
