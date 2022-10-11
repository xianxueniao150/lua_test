#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

static void stackDump(lua_State *L) {
  int i;
  int top = lua_gettop(L);
  for (i = -1; i >= -top; i--) { /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {
    case LUA_TSTRING: /* strings */
      printf("`%s'", lua_tostring(L, i));
      break;
    case LUA_TBOOLEAN: /* booleans */
      printf(lua_toboolean(L, i) ? "true" : "false");
      break;
    case LUA_TNUMBER: /* numbers */
      printf("%g", lua_tonumber(L, i));
      break;
    default: /* other values */
      printf("%s", lua_typename(L, t));
      break;
    }
    printf("\n"); /* put a separator */
  }
  printf("------------\n"); /* end the listing */
}

int main(int argc, char const *argv[]) {
  lua_State *l = luaL_newstate();
  lua_pushboolean(l, 1);
  lua_pushnumber(l, 10);
  lua_pushstring(l, "hello");

  stackDump(l);

  lua_replace(l, -2);
  stackDump(l);

  return 0;
}