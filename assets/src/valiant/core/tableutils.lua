-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local tableutils = {}

function tableutils.copy(t)
    local u = { }
    for k, v in pairs(t) do u[k] = v end
    return setmetatable(u, debug.getmetatable(t))
  end

function tableutils.merge(t1, t2)
    for k,v in pairs(t2) do t1[k] = v end
    return t1
end

return tableutils
