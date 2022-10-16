--file: testEnv.lua

s = "outer"

print(s)

do
    local _ENV = {
        print = print -- import print
    }
    s = "inner"
    print(s)
end

print(s)

print(_ENV == _G) -- prints true, since the default _ENV is set to the global table

local function setEnv(t)
    assert(type(t) == "table", "Notice: The env you pass " .. type(t) .. " is not a table .")
    local print = print
    local _ENV = t
    --get the local variable x , y  and print , as same as _ENV.x , _ENV.y , _ENV.print
    -- print("pos x : " .. x .. " pos y : " .. y) -- pos x : 800 pos y : 500
    print("aaaj")
end

local env = { x = 800, y = 500 }
setEnv(env)
