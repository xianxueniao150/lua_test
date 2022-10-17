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

    // �������Эͬ����
    // ���ﷵ��LUA_YIELD
    bRet = lua_resume(L1, 1, 0);
    cout << "bRet:" << bRet << endl;

    // ��ӡL1ջ��Ԫ�صĸ���
    cout << "Element Num:" << lua_gettop(L1) << endl;

    // ��ӡyield���ص�����ֵ
    cout << "Value 1:" << lua_tointeger(L1, -2) << endl;
    cout << "Value 2:" << lua_tointeger(L1, -1) << endl;

    // �ٴ�����Эͬ����
    // ���ﷵ��0
    bRet = lua_resume(L1, 0);
    cout << "bRet:" << bRet << endl;

    cout << "Element Num:" << lua_gettop(L1) << endl;
    cout << "Value 1:" << lua_tointeger(L1, -1) << endl;

    lua_close(L);

    return 0;
}