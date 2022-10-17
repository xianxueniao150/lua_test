--corTest.lua
function CorTest()
    print("coroutine begin")
    local re = coroutine.yield(100, "hello c++")
    print("coroutine continue: " .. re)
    Stop("call c yield!")
    print("coroutine continue after yield")
    print("coroutine end")
end
