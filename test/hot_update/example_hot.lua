package.path = "/home/ubuntu/project/lua/test/hot_update/?.lua"
local oldfunc = require "example"
oldfunc() --1
oldfunc() --2
package.loaded["example"] = nil
local newfunc = require "example"

for i = 1, math.huge do
    local name, value = debug.getupvalue(oldfunc, i)
    if not name then break end
    debug.setupvalue(newfunc, i, value)
end

newfunc() --3
newfunc() --4
