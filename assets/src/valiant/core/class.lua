-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

---comment
---@param fields table A table of fields to initialize the instance.
---@return table instance The new class.
local function class(fields)
    if type(fields) ~= "table" then fields = {} end
    local NewClass = {}
    NewClass.__index = NewClass
    ---Initialize this instance.
    function NewClass:__init(...) end
    ---Create a new instance of this class.
    ---@return table instance An instance of this class.
    function NewClass.create(...) -- TODO: @valiant-lang/feature `...` -> `args...`
        local instance = fields
        setmetatable(instance, NewClass)
        instance:__init(...) -- TODO: @valiant-lang/feature `unpack(arg)` -> `...args`
        return instance
    end
    return NewClass
end

return class
