function greet(a, b)
    print("param:", a, b)
end

co = coroutine.create(greet) -- 创建 coroutine
print("resume return:", coroutine.resume(co, "a1", "a2")) -- 输出 resume return:  true y1  y2 (resume 的返回值)
