-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local function merge(t1, t2)
    for k,v in pairs(t2) do t1[k] = v end
end

return {
    merge = merge
}
