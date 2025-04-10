local stringutils = {}

---Returns `true` if `str` starts with `substr`; otherwise, `false`.
---@param str string
---@param substr string
---@return boolean
function stringutils.startsWith(str, substr)
    if str:sub(#substr) == substr then return true end
    return false
end

return stringutils
