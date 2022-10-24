--main.lua
function foo(x)
    --接收到10,20
    print("foo", coroutine.yield(10, x)) --foo     10      21
end

function foo1(x)
    foo(x + 1)
    return 3
end
