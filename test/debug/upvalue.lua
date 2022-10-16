function newCounter()
    local n = 0
    local k = 0
    return function()
        k = n
        n = n + 1
        return n
    end
end

counter = newCounter()
counter()
counter()
-- 此时"k"是1，"n"是2。

local i = 1
repeat
    name, val = debug.getupvalue(counter, i)
    if name then
        print("index", i, name, "=", val) -- 依次输出两个"upvalues"的名字和值。
        if (name == "n") then
            debug.setupvalue(counter, i, 10) -- 设置"n"的值为10。
        end
        i = i + 1
    end
until not name

-- 在此调用后"n"的值被加1，变为11。
print(counter())
--[[ results: 
     index    1    k    =    1
     index    2    n    =    2
     11
]]