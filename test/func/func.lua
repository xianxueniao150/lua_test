function foo()
end

function foo1()
    return "a"
end

function foo2()
    return "a", "b"
end

x, y = foo2(), 20 -- x = "a", y = 20
print(x, y)
x, y = foo(), 20, 30 -- x = nil, y = 20
print(x, y)
print(foo2() .. "x") -- ax  在表达式中调用foo2
t = { foo(), foo2(), 4 } --t[1] = nil, t[2] = "a", t[3] == 4
print(t[1], t[2], t[3])
print((foo2())) --> a

function add(...)
    local s = 0
    for _, v in ipairs { ... } do
        s = s + v
    end
    return s
end

print(add(3, 4, 10, 25, 12)) -->54

function nonils(...)
    local arg = table.pack(...)
    for i = 1, arg.n do
        if (arg[i] == nil) then
            return false
        end
    end
    return true
end

function add(...)
    local s = 0
    for i = 1, select("#", ...) do
        s = s + select(i, ...)
    end
    return s
end
