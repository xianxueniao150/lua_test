//main.c
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

//在Lua Code中注册的函数
int sum_closure(lua_State *L) { //到该函数被调用时,可以通过lua_upvalueindex()函数获取到该函数的closure
    int c1 = (int)lua_tonumber(L, lua_upvalueindex(1));
    int c2 = (int)lua_tonumber(L, lua_upvalueindex(2));
    int top = lua_gettop(L);
    int sum = c1 + c2;
    for (size_t t = top; t > 0; t--) {
        int lnum = lua_tonumber(L, t);
        sum += lnum;
    }
    //把结果值压入虚拟栈返回
    lua_pushnumber(L, sum);
    return 1;
}

void main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    //加载并执行代码
    if (luaL_loadfile(L, "main.lua")) {
        //如果失败，栈顶为错误信息
        printf("loadfile failed! %s\n", lua_tostring(L, -1));
    }

    //与sum_closure()函数管理的closure管理的值
    lua_pushnumber(L, 100);
    lua_pushnumber(L, 2000);
    //压入c函数
    lua_pushcclosure(L, sum_closure, 2);
    lua_setglobal(L, "sum"); //设置到全局变量名c_func
    lua_pcall(L, 0, 0, 0);
}