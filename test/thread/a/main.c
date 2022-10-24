//main.c
#include <stdio.h>
#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

void main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, "main.lua") || lua_pcall(L, 0, 0, 0))
        printf("loadfile failed! %s\n", lua_tostring(L, -1)); //如果失败，栈顶为错误信息

    lua_State *L1 = lua_newthread(L); //创建新协程

    //在协程里调用 foo1 函数
    lua_getglobal(L1, "foo1");
    lua_pushinteger(L1, 20);

    //如果遇到 lua 代码的 yield，那么 i = 1
    //此时，栈里就是 coroutine.yield 里面的参数，10,20
    int i = lua_resume(L1, NULL, 1); //1(LUA_YIELD)

    printf("%d\n", lua_gettop(L1)); //-->栈里的参数个数 2

    //栈里的参数值
    printf("%lld\n", lua_tointeger(L1, 1)); //--> 10
    printf("%lld\n", lua_tointeger(L1, 2)); //--> 21

    //重新运行，并从当前栈里传递2个参数(10,20)
    i = lua_resume(L1, NULL, 2); //i=0 代表结束

    //此时返回一个结果3
    printf("%d\n", lua_gettop(L1));         //--> 1
    printf("%lld\n", lua_tointeger(L1, 1)); //--> 3
}