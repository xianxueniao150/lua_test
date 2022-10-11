//main.c
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

static int l_cf(lua_State *L) {
    double d = luaL_checknumber(L, 1); //校验并获取
    lua_pushnumber(L, d + 1);          //第一个返回值压入栈
    lua_pushnumber(L, d + 2);          //第二个返回值压入栈
    return 2;                          //返回值个数
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
    lua_pushcfunction(L, l_cf);
    lua_setglobal(L, "c_func"); //设置到全局变量名c_func

    //获取全局变量函数并压入栈顶
    lua_getglobal(L, "foo");

    //压入2个参数
    lua_pushinteger(L, 2);
    lua_pushinteger(L, 3);

    //调用函数，2个传入参数，3个返回参数
    //调用完后弹出3个元素
    if (lua_pcall(L, 2, 3, 0) != 0) {
        printf("error running function ’f’: %s", lua_tostring(L, -1));
        return;
    }
    //如果调用成功，3个返回结果压入栈

    int a = lua_tointeger(L, -3); //获取第1个返回值
    int b = lua_tointeger(L, -2); //获取第2个返回值
    int c = lua_tointeger(L, -1); //获取第3个返回值

    printf("%d,%d,%d\n", a, b, c); //5,2,3
}