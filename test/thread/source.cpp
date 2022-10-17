#include <iostream>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

using namespace std;

int main() {
    lua_State *L = luaL_newstate();
    if (!L) {
        return 0;
    }

    luaL_openlibs(L);

    lua_State *L1 = lua_newthread(L);
    if (!L1) {
        return 0;
    }

    int bRet = luaL_loadfile(L, "test.lua");
    if (bRet) {
        return 0;
    }

    bRet = lua_pcall(L, 0, 0, 0);
    if (bRet) {
        return 0;
    }

    lua_getglobal(L1, "Func1");
    lua_pushinteger(L1, 10);

    // 运行这个协同程序
    // 这里返回LUA_YIELD
    bRet = lua_resume(L1, 1, 0);
    cout << "bRet:" << bRet << endl;

    // 打印L1栈中元素的个数
    cout << "Element Num:" << lua_gettop(L1) << endl;

    // 打印yield返回的两个值
    cout << "Value 1:" << lua_tointeger(L1, -2) << endl;
    cout << "Value 2:" << lua_tointeger(L1, -1) << endl;

    // 再次启动协同程序
    // 这里返回0
    bRet = lua_resume(L1, 0);
    cout << "bRet:" << bRet << endl;

    cout << "Element Num:" << lua_gettop(L1) << endl;
    cout << "Value 1:" << lua_tointeger(L1, -1) << endl;

    lua_close(L);

    return 0;
}