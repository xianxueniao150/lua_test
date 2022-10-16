local function getupvaluetable(u, func, unique)
    local i = 1
    while true do
        local name, value = debug.getupvalue(func, i)
        if name == nil then
            return
        end
        local t = type(value)
        if t == "table" or t == "number" or t == "string" then
            u[name] = value
        elseif t == "function" then
            if not unique[value] then
                unique[value] = true
                getupvaluetable(u, value, unique)
            end
        end
        i = i + 1
    end
end

-- main.lua
local m = require "m"
m.add() -- a = 2
m.add() -- a = 3
m.add() -- a = 4

local u = {}
local unique = {}
getupvaluetable(u, m.add, unique)
local env = setmetatable({ u = u, m = m }, { __index = _ENV })
loadfile("./hotfix.lua", "bt", env)()

m.add() -- a = 6
m.add() -- a = 8
