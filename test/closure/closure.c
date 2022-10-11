//main.c
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

//在Lua Code中注册的函数
int sum(lua_State *L) {
    int top = lua_gettop(L);
    int sum = 0;
    for (size_t t = top; t > 0; t--) {
        int lnum = lua_tonumber(L, t);
        sum += lnum;
    }
    lua_pushnumber(L, sum);
    return 1;
}

void main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    //加载并执行代码
    if (luaL_loadfile(L, "main.lua") || lua_pcall(L, 0, 0, 0)) {
        //如果失败，栈顶为错误信息
        printf("loadfile failed! %s\n", lua_tostring(L, -1));
    }

    //压入c函数
    lua_pushcclosure(L, sum, 0);
    lua_setglobal(L, "sum"); //设置到全局变量名c_func

    //获取全局变量函数并压入栈顶
    lua_getglobal(L, "foo");
}