function traceback()
    for level = 1, math.huge do
        local info = debug.getinfo(level, "Sl")
        if not info then break end
        if info.what == "C" then
            print(string.format("%d\tC function", level))
        else
            print(string.format("%d\t[%s]:%d", level, info.short_src, info.currentline))
        end
    end
end

traceback()
