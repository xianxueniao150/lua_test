function trace(event, line)
     local s = debug.getinfo(2).short_src
     print(s .. ":" .. line)
end

debug.sethook(trace, "l")

function foo()
     local a = 1
end

local x = 1
foo()
