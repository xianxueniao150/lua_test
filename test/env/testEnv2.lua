local print, sin = print, math.sin
_ENV = nil
print(13) -->13
print(sin(13)) -->0.42016703682664
print(_G.math.cos(13)) -- error!
