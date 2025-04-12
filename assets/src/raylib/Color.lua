local Color = {}

function Color.create(r, g, b, a)
    if type(r) == "table" then
        local color = r
        if type(color.r) == "number" then
            r = color.r
            g = color.g
            b = color.b
            a = color.a
        else
            r = color[1]
            g = color[2]
            b = color[3]
            a = color[4]
        end
    end
    if type(r) ~= "number" then r = 0 end
    if type(g) ~= "number" then g = 0 end
    if type(b) ~= "number" then b = 0 end
    if type(a) ~= "number" then a = 255 end
    return vstdlib_raylib_Color_create(r, g, b, a)
end

function Color.r(color, value)
    return vstdlib_raylib_Color_r(color, value)
end

function Color.g(color, value)
    return vstdlib_raylib_Color_g(color, value)
end

function Color.b(color, value)
    return vstdlib_raylib_Color_b(color, value)
end

function Color.a(color, value)
    return vstdlib_raylib_Color_a(color, value)
end

Color.ASHPINK = Color.create(0xFF, 0x00, 0x69, 0xFF)
Color.BLACK = Color.create(0x00, 0x00, 0x00, 0xFF)
Color.BLUE = Color.create(0x00, 0x00, 0xFF, 0xFF)
Color.GREEN = Color.create(0x00, 0xFF, 0x00, 0xFF)
Color.PINK = Color.create { 255, 109, 194, 255 }
Color.RAYWHITE = Color.create { 245, 245, 245, 255 }
Color.RED = Color.create(0xFF, 0x00, 0x00, 0xFF)
Color.SKYBLUE = Color.create { 102, 191, 255, 255 }
Color.WHITE = Color.create(0xFF, 0xFF, 0xFF, 0xFF)
Color.YELLOW = Color.create(0xFF, 0xFF, 0x00, 0xFF)

return Color
