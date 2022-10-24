-- m.lua
local m = {}

m.b = 6

local a = 1

function m.add()
    a = a + 1
    print("a", a)
end

return m
