//! main.c  gcc main.c -o test -I../../lua-5.3.6/src -L../../lua-5.3.6/src -llua -lm -ldl
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>

static int Stop(lua_State *L);
lua_State *CreateCoroutine(lua_State *gL, const char *corName);

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "corTest.lua");
    lua_State *newL = CreateCoroutine(L, "CorTest");
    lua_register(newL, "Stop", Stop);
    int re = lua_resume(newL, NULL, 0);
    if (re != LUA_YIELD) {
        printf("ERROR");
        return 0;
    }

    int rint = luaL_checknumber(newL, -2);
    const char *str = lua_tostring(newL, -1);
    printf("stack value: %d,  %s,now stack size:%d\n", rint, str, lua_gettop(newL));
    lua_pushstring(newL, "from c++");
    re = lua_resume(newL, NULL, 1);
    printf("555 stack szie: %d\n", lua_gettop(newL));
    re = lua_resume(newL, NULL, 0);
    lua_close(L);
    return 0;
}

static int Stop(lua_State *lp) {
    const char *str = lua_tostring(lp, -1);
    printf("C Stop Func: %s\n", str);
    lua_pushstring(lp, str);
    printf("Stop func stack szie: %d\n", lua_gettop(lp));
    return lua_yield(lp, 1);
}

lua_State *CreateCoroutine(lua_State *gL, const char *corName) {
    lua_State *newL = lua_newthread(gL);
    lua_getglobal(newL, corName);
    return newL;
}