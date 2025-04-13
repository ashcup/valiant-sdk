-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local tableutils = require "valiant.core.tableutils"

local function instanceof(instance, class)
    local classType = type(class)
    if classType == "string" then
        return type(instance) == class
    elseif classType == "table" then
        return getmetatable(instance) == class
    end
    return instance == class
end

---comment
---@param fields table A table of fields to initialize the instance.
---@return table instance The new class.
local function class(fields)
    if type(fields) ~= "table" then fields = {} end
    fields = tableutils.copy(fields)
    if type(fields.__extends) ~= "table" then fields.__extends = {} end
    local extends = fields.__extends
    fields.__extends = nil
    ---@class NewClass The new class being defined.
    local NewClass = {}
    for _, ParentClass in pairs(extends) do
        tableutils.merge(NewClass, ParentClass)
    end
    NewClass.__index = NewClass
    ---Initialize this instance.
    function NewClass:__init(...) end
    ---Create a new instance of this class.
    ---@return table instance An instance of this class.
    function NewClass.create(...) -- TODO: @valiant-lang/feature `...` -> `args...`
        local instance = tableutils.copy(fields)
        setmetatable(instance, NewClass)
        instance:__init(...) -- TODO: @valiant-lang/feature `unpack(arg)` -> `...args`
        return instance
    end
    return NewClass
end

return {
    class = class,
    instanceof = instanceof
}
