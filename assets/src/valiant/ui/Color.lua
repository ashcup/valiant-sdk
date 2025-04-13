local raylib = require "raylib"

local Color = class {
    r = 0.0,
    g = 0.0,
    b = 0.0,
    a = 1.0
}

Color.BYTE_TO_FLOAT_SCALE = 0.00392156862745098;
Color.FLOAT_TO_BYTE_SCALE = 255.0;

function Color:__init(r, g, b, a)
    if type(r) ~= "number" then r = 0.0 end
    if type(g) ~= "number" then g = 0.0 end
    if type(b) ~= "number" then b = 0.0 end
    if type(a) ~= "number" then a = 1.0 end
    self.r = r
    self.g = g
    self.b = b
    self.a = a
end

function Color.fromHex(r, g, b, a)
    local byteToFloatScale = Color.BYTE_TO_FLOAT_SCALE
    if type(r) ~= "number" then r = 0x00 end
    if type(g) ~= "number" then g = 0x00 end
    if type(b) ~= "number" then b = 0x00 end
    if type(a) ~= "number" then a = 0xFF end
    return Color.create(
        byteToFloatScale * r,
        byteToFloatScale * g,
        byteToFloatScale * b,
        byteToFloatScale * a
    )
end

---Create a new `valiant.ui.Color` from a `raylib.Color`.
---@param raylibColor userdata The raylib color.
---@return table color The color.
function Color.fromRaylib(raylibColor)
    print "raylib color {"
    print("    r = " .. raylib.Color.r(raylibColor))
    print("    g = " .. raylib.Color.g(raylibColor))
    print("    b = " .. raylib.Color.b(raylibColor))
    print("    a = " .. raylib.Color.a(raylibColor))
    print "}"
    local byteToFloatScale = Color.BYTE_TO_FLOAT_SCALE
    return Color.create(
        byteToFloatScale * raylib.Color.r(raylibColor),
        byteToFloatScale * raylib.Color.g(raylibColor),
        byteToFloatScale * raylib.Color.b(raylibColor),
        byteToFloatScale * raylib.Color.a(raylibColor)
    )
end

---Convert this `valiant.ui.Color` into a `raylib.Color`.
---@return unknown
function Color:build()
    -- print "Color {"
    -- for k, v in pairs(self) do
    --     print("    " .. k .. " = " .. v)
    -- end
    -- print "}"
    local floatToByteScale = Color.FLOAT_TO_BYTE_SCALE;
    return raylib.Color.create(
        math.floor(0.5 + (floatToByteScale * self.r)),
        math.floor(0.5 + (floatToByteScale * self.g)),
        math.floor(0.5 + (floatToByteScale * self.b)),
        math.floor(0.5 + (floatToByteScale * self.a))
    )
end

Color.ASHPINK = Color.fromRaylib(raylib.Color.ASHPINK)
Color.BLACK = Color.fromRaylib(raylib.Color.BLACK)
Color.BLUE = Color.fromRaylib(raylib.Color.BLUE)
Color.GREEN = Color.fromRaylib(raylib.Color.GREEN)
Color.PINK = Color.fromRaylib(raylib.Color.PINK)
Color.RAYWHITE = Color.fromRaylib(raylib.Color.RAYWHITE)
Color.RED = Color.fromRaylib(raylib.Color.RED)
Color.SKYBLUE = Color.fromRaylib(raylib.Color.SKYBLUE)
Color.WHITE = Color.fromRaylib(raylib.Color.WHITE)
Color.YELLOW = Color.fromRaylib(raylib.Color.YELLOW)

return Color
