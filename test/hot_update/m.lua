-- m.lua
local m = {}

local a = 1

function m.add()
    a = a + 1
    print("a", a)
end

return m
