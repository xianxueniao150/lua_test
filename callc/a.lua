local mylib = require "mylib"

local objStudent = mylib.new()

objStudent:setName("果冻想")
objStudent:setAge(15)

print(objStudent:getName())
print(objStudent:getAge())
print(objStudent)
