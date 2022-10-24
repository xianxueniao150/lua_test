print(not nil) --true
print(not "a") --false
print("b" or "a") --b
print(nil or "a") --a
print("b" and "a") --a
function fa(a)
    print(not a)
end

print(fa())
