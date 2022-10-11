--main.lua
function foo(x, y)
    a = x + y
    b, c = c_func(1) --调用C函数
    return a, b, c
end
