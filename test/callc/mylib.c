#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

typedef struct StudentTag {
  const char *name; // 学生姓名
  int age;          // 学生年龄
} StudentTag;

static int Student(lua_State *L) {
  size_t iBytes = sizeof(StudentTag);
  StudentTag *pStudent = (StudentTag *)lua_newuserdata(L, iBytes);

  // 设置元表
  luaL_getmetatable(L, "Student");
  lua_setmetatable(L, -2);

  return 1; // 新的userdata已经在栈上了
}

static int GetName(lua_State *L) {
  struct StudentTag *pStudent =
      (struct StudentTag *)luaL_checkudata(L, 1, "Student");
  lua_pushstring(L, pStudent->name);

  return 1;
}

static int SetName(lua_State *L) {
  // 第一个参数是userdata
  struct StudentTag *pStudent =
      (struct StudentTag *)luaL_checkudata(L, 1, "Student");

  // 第二个参数是一个字符串
  const char *pName = luaL_checkstring(L, 2);
  luaL_argcheck(L, pName != NULL && pName != "", 2, "Wrong Parameter");
  pStudent->name = pName;
  return 0;
}

static int GetAge(lua_State *L) {
  // 第一个参数是userdata
  struct StudentTag *pStudent =
      (struct StudentTag *)luaL_checkudata(L, 1, "Student");
  lua_pushinteger(L, pStudent->age);
  return 1;
}

static int SetAge(lua_State *L) {
  // 第一个参数是userdata
  struct StudentTag *pStudent =
      (struct StudentTag *)luaL_checkudata(L, 1, "Student");

  int iAge = luaL_checkinteger(L, 2);
  luaL_argcheck(L, iAge >= 6 && iAge <= 100, 2, "Wrong Parameter");
  pStudent->age = iAge;
  return 0;
}

static int tostring(lua_State *L) {
  struct StudentTag *pStudent =
      (struct StudentTag *)luaL_checkudata(L, 1, "Student");
  lua_pushfstring(L, "student(name=%s,age=%d)", pStudent->name, pStudent->age);
  return 1;
}

static const struct luaL_Reg mylib_f[] = {{"new", Student}, {NULL, NULL}};

static const struct luaL_Reg mylib_m[] = {
    {"getName", GetName}, {"setName", SetName},     {"getAge", GetAge},
    {"setAge", SetAge},   {"__tostring", tostring}, {NULL, NULL}};

extern int luaopen_mylib(lua_State *L) {
  luaL_newmetatable(L, "Student"); //创建元表
  lua_pushvalue(L, -1);            //复制元表
  lua_setfield(L, -2, "__index");  //元表.__index = 元表
  luaL_setfuncs(L, mylib_m, 0);    //注册元方法
  luaL_newlib(L, mylib_f);         //创建库
  return 1;
}
