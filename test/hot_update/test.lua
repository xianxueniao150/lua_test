package.path = "/home/ubuntu/project/lua/test/hot_update/?.lua"
function Sleep(n)
    os.execute("sleep " .. n)
end

function reload_module(module_name)
    local old_module = package.loaded[module_name] or {}
    package.loaded[module_name] = nil
    require(module_name)

    local new_module = package.loaded[module_name]
    for k, v in pairs(new_module) do
        old_module[k] = v
    end

    package.loaded[module_name] = old_module
    return old_module
end

g = {}

for i = 1, 5 do
    local m = reload_module("m")
    if (i == 1) then g = m end
    print('m.b is ', m.b)
    print('g.b is ', g.b)
    Sleep(5)
end
